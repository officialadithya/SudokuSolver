/*

Name of this C++ program: Sudoku Solver

Programmer: Bhaskara, Adithya

Brief Description of this program.

  This program solves a sudoku board given in "board.txt"
  using the backtracking algorithm.

*/

// Include "iostream" Library for Input/Output
#include <iostream>

// Include "fstream" Library for File Streams
#include <fstream>

// Include "cstdlib" Library for Exit on Error
#include <cstdlib>

// Include "sstream" Library for String Stream
#include <sstream>

// Include "string" Library for Strings
#include <string>

// Using Standard Namespace
using namespace std;

// Declare Constant Int for Board Dimensions & Constant String for Filename
const int BOARD_SIZE = 9;
const string FILENAME = "../assets/board.txt";

// Function Prototypes
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]);
int* tokenize(string text);
void readBoard(const string FILENAME, int board[BOARD_SIZE][BOARD_SIZE]);
int* findEmpty(int board[BOARD_SIZE][BOARD_SIZE]);
bool isValid(int board[BOARD_SIZE][BOARD_SIZE], int rowIndex, int colIndex, int placement);
bool solve(int board[BOARD_SIZE][BOARD_SIZE]);

// Main Function -- Entry Point
int main() {

    int board[BOARD_SIZE][BOARD_SIZE];
    readBoard(FILENAME, board);
    
    cout << "The Board to Solve:" << endl;
	printBoard(board);

	cout << endl;
    solve(board);

	cout << "The Solved Board:" << endl;
    printBoard(board);

    return 0;

}

/**
 * printBoard() prints the sudoku board.
 * @param board : A 2D array containing the board.
 * @return : NONE
 */
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {

    // Iterate Over 2D Array
    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {

            // Print Element
            cout << board[i][j] << " ";

        }

        // Newline
        cout << endl;

    }

}

/**
 * tokenize() splits a string into an array.
 * @param text : The string to tokenize.
 * @return : A pointer to an array containing the tokenized string.
 */
int* tokenize(string text) {

    // Dynamically Allocate Row Array
    int* row = new int[BOARD_SIZE];

    // Declare String Stream Object and Token String
    stringstream ss(text);
    string token;

    // Read From String Stream Into Token
    for (int i = 0; ss >> token; i++) {

        // Convert to Integer & Place Into Array
        int num = stoi(token);
        row[i] = num;

    }

    // Return Pointer to Array
    return row;

}

/**
 * readBoard() reads the board into a 2D array from a file.
 * @param FILENAME : The filename to be read.
 * @param board : The 2D array to store the board into.
 */
void readBoard(const string FILENAME, int board[BOARD_SIZE][BOARD_SIZE]) {

    // Declare File Stream Object
    ifstream file(FILENAME);

    // Display Error Message if File Failed
    if (file.fail()) {
        cout << "An Error Reading the Board has Occured." << endl;
        exit(1);
    }

    // Declare String for Each Line of File
    string line;

    // Read From File Stream Into Line
    for (int i = 0; getline(file, line); i++) {

        // Tokenize Line of File
        int* row = tokenize(line);

        for (int j = 0; j < BOARD_SIZE; j++) {

            // Place Into Board
            board[i][j] = *(row+j);

        }

        // Deallocate Tokenized Row Array
        delete[] row;

    }

}

/**
 * findEmpty() finds empty coordinates in the board.
 * @param board : A 2D array containing the board.
 * @return : A pointer to an array of two elements containing the coordinates of an empty space.
 */
int* findEmpty(int board[BOARD_SIZE][BOARD_SIZE]) {

    // Dynamically Allocate Coordinate Array
    int* coords = new int[2];

    // Iterate Over 2D Array
    for (int i = 0; i < BOARD_SIZE; i++) {

        for (int j = 0; j < BOARD_SIZE; j++) {

            // If Empty Space Found, Place Coords Into Array & Return
            if (board[i][j] == 0) {
                coords[0] = i;
                coords[1] = j;
                return coords;

            }

        }

    }

    // Return [-1, -1] if Empty Coordinates Not Found
    coords[0] = -1;
    coords[1] = -1;
    return coords;

}

/**
 * isValid() checks if a given entry to the board is valid
 * @param board : A 2D array containing the board.
 * @param rowIndex : The row index of the move.
 * @param colIndex : The column index of the move.
 * @param placement : The numerical value of the move.
 * @return : A boolean representing the validity of the board state.
 */
bool isValid(int board[BOARD_SIZE][BOARD_SIZE], int rowIndex, int colIndex, int placement) {

    // Return False if Duplicate Found in Row | Column Index Changes
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[rowIndex][i] == placement) return false;
    }

    // Return False if Duplicate Found in Column | Row Index Changes
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][colIndex] == placement) return false;
    }

	// Integer Division to Find Which Square to Search (Think of a 2D Array of the Squares)
	int sqrRow = rowIndex / 3;
	int sqrCol = colIndex / 3;

	// Iterate Over the Square & Return False if Duplicate Found in Square (Algorithm by Tech With Tim)
	for (int i = sqrRow*3; i < sqrRow*3+3; i++) {
		for (int j = sqrCol*3; j < sqrCol*3+3; j++) {
			if (board[i][j] == placement) return false;
		}
	}

    // Return True if Not False
    return true;

}

/** solve() solves the sudoku board.
 * @param board : A 2D array containing the board.
 * @return : A boolean representing the solved state.
 */
bool solve(int board[BOARD_SIZE][BOARD_SIZE]) {

    // Dynamically Allocate Array to Get Coordinates of an Empty Space
    int* coords = findEmpty(board);
    int rowIndex = coords[0];
    int colIndex = coords[1];

    // Delete Coordinate Array
    delete[] coords;

    // If No Empty Spaces Left, the Board is Solved
    if (rowIndex == -1 && colIndex == -1) return true;
    
    // Backtracking
    for (int i = 1; i <= BOARD_SIZE; i++) {
        if (isValid(board, rowIndex, colIndex, i)) {
            board[rowIndex][colIndex] = i;
            if (solve(board)) return true;
            board[rowIndex][colIndex] = 0;
        }
    }

    return false;

}
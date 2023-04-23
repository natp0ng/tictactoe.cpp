#include <iostream>
#include <string>

const int BOARD_SIZE = 3;
const char EMPTY = ' ';
const char X_MARKER = 'X';
const char O_MARKER = 'O';

using namespace std;

class Board {
public:
  // Constructor
  Board();

  // Public member functions
  void print() const;
  bool isGameOver() const;
  char getWinner() const;
  bool makeMove(int row, int col, char marker);
  int getNumMoves() { return m_numMoves; };

private:
  // Private member variables
  char m_grid[BOARD_SIZE][BOARD_SIZE];
  int m_numMoves;

  // Private member functions
  bool isCellValid(int row, int col) const;
  bool isCellEmpty(int row, int col) const;
  bool checkRow(int row) const;
  bool checkCol(int col) const;
  bool checkDiagonal1() const;
  bool checkDiagonal2() const;
};

// Constructor
Board::Board() {
  // Initialize the grid to all empty cells
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      m_grid[row][col] = EMPTY;
    }
  }

  // Initialize the number of moves to 0
  m_numMoves = 0;
}

// Public member functions

void Board::print() const {
  // Clear the screen
  cout << "\033[2J";

  // Move the cursor to row 1, column 1
  cout << "\033[1;1H";

  // Print the column numbers
  cout << " ";
  for (int col = 0; col < BOARD_SIZE; ++col) {
    cout << " " << col + 1;
  }
  cout << endl;

  // Print the rows
  for (int row = 0; row < BOARD_SIZE; ++row) {
    // Print the row number
    cout << row + 1 << "|";

    // Print the cells in the row
    for (int col = 0; col < BOARD_SIZE; ++col) {
      cout << m_grid[row][col] << "|";
    }

    // Print a newline after the row
    cout << endl;
  }
}

bool Board::isGameOver() const {
  // Check if there is a winning line
  if (getWinner() != EMPTY) {
    return true;
  }

  // Check if the board is full
  return m_numMoves == BOARD_SIZE * BOARD_SIZE;
}

char Board::getWinner() const {
  // Check all rows for a winning line
  for (int row = 0; row < BOARD_SIZE; ++row) {
    if (checkRow(row)) {
      return m_grid[row][0];
    }
  }

  // Check all columns for a winning line
  for (int col = 0; col < BOARD_SIZE; ++col) {
    if (checkCol(col)) {
      return m_grid[0][col];
    }
  }

  // Check both diagonals for a winning line
  if (checkDiagonal1()) {
    return m_grid[0][0];
  }

  if (checkDiagonal2()) {
    return m_grid[0][2];
  }

  // No winning line found
  return EMPTY;
}

bool Board::makeMove(int row, int col, char marker) {
  // Check if the cell is valid and empty
  if (!isCellValid(row, col) || !isCellEmpty(row, col)) {
    return false;
  }

  // Place the marker in the cell
  m_grid[row][col] = marker;

  // Increment the number of moves
  ++m_numMoves;

  return true;
}

// Private member functions

bool Board::isCellValid(int row, int col) const {
  // Check if the row and column are within the bounds of the grid
  if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
    return false;
  }

  // The cell is valid if it is not already occupied
  return m_grid[row][col] == EMPTY;
}

bool Board::isCellEmpty(int row, int col) const {
  // Check if the cell is within the bounds of the grid
  if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
    return false;
  }

  // The cell is empty if it contains the EMPTY marker
  return m_grid[row][col] == EMPTY;
}

bool Board::checkRow(int row) const {
  // Check if all cells in the row have the same non-EMPTY marker
  return (m_grid[row][0] != EMPTY && m_grid[row][0] == m_grid[row][1] &&
          m_grid[row][1] == m_grid[row][2]);
}

bool Board::checkCol(int col) const {
  // Check if all cells in the column have the same non-EMPTY marker
  return (m_grid[0][col] != EMPTY && m_grid[0][col] == m_grid[1][col] &&
          m_grid[1][col] == m_grid[2][col]);
}

bool Board::checkDiagonal1() const {
  // Check if all cells in the diagonal have the same non-EMPTY marker
  return (m_grid[0][0] != EMPTY && m_grid[0][0] == m_grid[1][1] &&
          m_grid[1][1] == m_grid[2][2]);
}

bool Board::checkDiagonal2() const {
  // Check if all cells in the diagonal have the same non-EMPTY marker
  return (m_grid[0][2] != EMPTY && m_grid[0][2] == m_grid[1][1] &&
          m_grid[1][1] == m_grid[2][0]);
}

// Main function

int main() {
  // Initialize the game board
  Board board;

  // Start the game loop
  while (!board.isGameOver()) {
    // Print the board
    board.print();

    // Get the player's move
    int row, col;
    cout << "Enter row and column for ["
         << (board.getNumMoves() % 2 == 0 ? X_MARKER : O_MARKER)
         << "] (example:1 1): ";
    cin >> row >> col;

    // Make the move
    if (!board.makeMove(row - 1, col - 1,
                        (board.getNumMoves() % 2 == 0 ? X_MARKER : O_MARKER))) {
      cout << "Invalid move. Please try again." << endl;
    }
  }

  // Print the final board
  board.print();

  // Print the winner
  char winner = board.getWinner();
  cout << "Game over. ";
  if (winner == EMPTY) {
    cout << "It's a tie!" << endl;
  } else {
    cout << "Player " << winner << " wins!" << endl;
  }

  return 0;
}

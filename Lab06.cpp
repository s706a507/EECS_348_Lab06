#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

// Define a type alias for a matrix using vectors
using Matrix = std::vector<std::vector<int> >;

// Function to read matrices from a file
Matrix readMatrixFromFile(const std::string &filePath, int &matrixSize) {
   std::ifstream file(filePath); // Open the file
   Matrix matrix; // Declare a matrix
   if (file) {
       file >> matrixSize; // Read the size of the matrix
       matrix.resize(matrixSize, std::vector<int>(matrixSize)); // Resize the matrix
       for (int i = 0; i < matrixSize; ++i) {
           for (int j = 0; j < matrixSize; ++j) {
               file >> matrix[i][j]; // Read matrix elements from the file
           }
       }
   } else {
       std::cerr << "Could not open file for reading." << std::endl; // Error message if file cannot be opened
   }
   return matrix; // Return the read matrix
}

// Function to print matrices
void printMatrix(const Matrix &matrix) {
   for (const auto &row : matrix) {
       for (int num : row) {
           std::cout << std::setw(4) << num; // Print each number in field of width 4
       }
       std::cout << std::endl;
   }
}

// Function to add two matrices
Matrix addMatrices(const Matrix &matrix1, const Matrix &matrix2, int matrixSize) {
   Matrix result(matrixSize, std::vector<int>(matrixSize, 0)); // Initialize result matrix with zeros
   for (int i = 0; i < matrixSize; ++i) {
       for (int j = 0; j < matrixSize; ++j) {
           result[i][j] = matrix1[i][j] + matrix2[i][j]; // Add corresponding elements
       }
   }
   return result; // Return the sum matrix
}

// Function to multiply two matrices
Matrix multiplyMatrices(const Matrix &matrix1, const Matrix &matrix2, int matrixSize) {
   Matrix result(matrixSize, std::vector<int>(matrixSize, 0)); // Initialize result matrix with zeros
   for (int i = 0; i < matrixSize; ++i) {
       for (int j = 0; j < matrixSize; ++j) {
           for (int k = 0; k < matrixSize; ++k) {
               result[i][j] += matrix1[i][k] * matrix2[k][j]; // Multiply and accumulate
           }
       }
   }
   return result; // Return the product matrix
}

// Function to subtract two matrices
Matrix subtractMatrices(const Matrix &matrix1, const Matrix &matrix2, int matrixSize) {
   Matrix result(matrixSize, std::vector<int>(matrixSize, 0)); // Initialize result matrix with zeros
   for (int i = 0; i < matrixSize; ++i) {
       for (int j = 0; j < matrixSize; ++j) {
           result[i][j] = matrix1[i][j] - matrix2[i][j]; // Subtract corresponding elements
       }
   }
   return result; // Return the difference matrix
}

// Function to update an element in a matrix
void updateMatrixElement(Matrix &matrix, int row, int col, int value) {
   if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix.size()) {
       matrix[row][col] = value; // Update the element if indices are valid
   } else {
       std::cerr << "Invalid row or column index." << std::endl; // Error message for invalid indices
   }
}

// Function to find the max value in a matrix
int findMaxValue(const Matrix &matrix) {
   int maxVal = matrix[0][0]; // Initialize max value with the first element
   for (const auto &row : matrix) {
       for (int num : row) {
           maxVal = std::max(maxVal, num); // Update max value if a greater element is found
       }
   }
   return maxVal; // Return the maximum value
}

// Function to transpose a matrix
Matrix transposeMatrix(const Matrix &matrix, int matrixSize) {
   Matrix transposed(matrixSize, std::vector<int>(matrixSize, 0)); // Initialize transposed matrix
   for (int i = 0; i < matrixSize; ++i) {
       for (int j = 0; j < matrixSize; ++j) {
           transposed[j][i] = matrix[i][j]; // Swap rows and columns
       }
   }
   return transposed; // Return the transposed matrix
}

int main() {
   // Path to your matrix data files
   std::string filePath = "matrix_input.txt";
   std::string filePath2 = "matrix_input2.txt";

   int matrixSize;
   // Read the first matrix from file
   Matrix firstMatrix = readMatrixFromFile(filePath, matrixSize);
   
   // Read the second matrix from file
   Matrix secondMatrix = readMatrixFromFile(filePath2, matrixSize);

   // Print the first matrix
   std::cout << "First Matrix:" << std::endl;
   printMatrix(firstMatrix);
   
   // Print the second matrix
   std::cout << "Second Matrix:" << std::endl;
   printMatrix(secondMatrix);

   // Add the two matrices and print the result
   std::cout << "Sum of Matrices:" << std::endl;
   Matrix sum = addMatrices(firstMatrix, secondMatrix, matrixSize);
   printMatrix(sum);

   // Multiply the two matrices and print the result
   std::cout << "Product of Matrices:" << std::endl;
   Matrix product = multiplyMatrices(firstMatrix, secondMatrix, matrixSize);
   printMatrix(product);

   // Subtract the second matrix from the first and print the result
   std::cout << "Difference of Matrices:" << std::endl;
   Matrix difference = subtractMatrices(firstMatrix, secondMatrix, matrixSize);
   printMatrix(difference);

   // Update an element in the first matrix and print the result
   std::cout << "Updating Element in First Matrix:" << std::endl;
   std::cout << "Changing 2nd row, 1st column to '99'" << std::endl;
   updateMatrixElement(firstMatrix, 1, 0, 99);
   printMatrix(firstMatrix);

   // Find the maximum value in the first matrix and print it
   int max = findMaxValue(firstMatrix);
   std::cout << "Max Value of First Matrix: " << max << std::endl;

   // Transpose the first matrix and print the result
   std::cout << "Transpose of the First Matrix:" << std::endl;
   Matrix transposedMatrix = transposeMatrix(firstMatrix, matrixSize);
   printMatrix(transposedMatrix);

   return 0;
}
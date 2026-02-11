find_smallest(int** matrix, int nrow, int ncol, int* rowCover, int* colCover,
                   int* minval) {
    for (int r = 0; r < nrow; r++)
        for (int c = 0; c < ncol; c++)
            if (rowCover[r] == 0 && colCover[c] == 0)
                *minval = MIN(*minval, matrix[r][c]);
}

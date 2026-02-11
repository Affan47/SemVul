find_star_in_col(int nrow, int** m, int c, int* r) {
    *r = -1;
    for (int i = 0; i < nrow; i++)
        if (m[i][c] == 1)
            *r = i;
}

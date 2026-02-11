print_matrix_f(double *m, int rows, int cols)
{
    int i,j,idx;

    for (i = 0; i < rows; ++i)
    {
        idx = i * cols;
        for (j = 0; j < cols; ++j)
            printf("%5.2f",m[idx+j]);
        printf("\n");
    }
}

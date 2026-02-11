matrix_mul_const(matrix_t *A, double c)
{
    matrix_t *mat = matrix_alloc(A->nrows, A->ncols);

    int i, j;
    for (i = 0; i < A->nrows; ++i)
        for (j = 0; j < A->ncols; ++j)
            mat->data[i][j] = A->data[i][j] * c;

    return mat;
}

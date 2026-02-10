matrix_row_sub_index(matrix_t *A, matrix_t *s)
{
    int i, j, k;
    matrix_t *sub = matrix_alloc(s->nrows, A->ncols);
    k = 0;
    for (i = 0; i < A->nrows; ++i){
        if(i == (int)s->data[k][0]) {
            for (j = 0; j < A->ncols; ++j)
                sub->data[k][j] = A->data[i][j];
            ++k;
            if (k >= s->nrows)
                break;
        }
    }

    return sub;
}

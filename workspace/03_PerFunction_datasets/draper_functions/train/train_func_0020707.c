rand_multivariate_multiple(matrix_t *cov, double mu, int reps)
{
    matrix_t *A = matrix_cholesky(cov);
    matrix_t *res = matrix_alloc(reps, cov->nrows);
    matrix_t *z = matrix_alloc(cov->nrows, 1);
    int i;
    for (i = 0; i < reps; ++i){
        matrix_t *x = rand_multivariate_cholesky(A, mu, z);
        int j;
        for (j = 0; j < x->nrows; ++j)
            res->data[i][j] = x->data[j][0];
        matrix_free(x);
    }
    matrix_free(A);
    matrix_free(z);
    return res;
}

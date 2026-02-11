inverse_wishart_matrix (const gretl_matrix *S,
				      int v, int *err)
{
    gretl_matrix *C, *B = NULL, *W = NULL;
    double *Z = NULL;

    if (S == NULL || S->cols != S->rows || v < S->rows) {
	*err = E_INVARG;
	return NULL;
    }

    *err = 0;


    C = cholesky_factor_of_inverse(S, err);

    if (!*err) {
	*err = wishart_workspace(&W, &B, &Z, S->rows);
    }

    if (*err) {
	gretl_matrix_free(C);
	return NULL;
    }

    odell_feiveson_compute(W, Z, v);
    *err = wishart_inverse_finalize(C, B, W);

    if (*err) {
	gretl_matrix_free(W);
	W = NULL;
    }

    gretl_matrix_free(B);
    gretl_matrix_free(C);
    free(Z);

    return W;
}

get_SVD_ols_vcv (const gretl_matrix *A, const gretl_matrix *B,
		 const double *s, gretl_matrix *V, double *s2)
{
    double aik, ajk, vij;
    int m = A->cols;
    int i, j, k;


    for (i=0; i<m; i++) {
	for (j=i; j<m; j++) {
	    vij = 0.0;
	    for (k=0; k<m; k++) {
		if (s[k] > 0.0) {
		    aik = gretl_matrix_get(A, k, i);
		    ajk = gretl_matrix_get(A, k, j);
		    vij += aik * ajk / (s[k] * s[k]);
		}
	    }
	    gretl_matrix_set(V, i, j, vij);
	    if (j != i) {
		gretl_matrix_set(V, j, i, vij);
	    }
	}
    }

    if (s2 != NULL) {
	double sigma2 = 0.0;
	int T = A->rows;

	for (i=m; i<T; i++) {
	    sigma2 += B->val[i] * B->val[i];
	}
	sigma2 /= T - m;
	gretl_matrix_multiply_by_scalar(V, sigma2);
	*s2 = sigma2;
    }

    return 0;
}

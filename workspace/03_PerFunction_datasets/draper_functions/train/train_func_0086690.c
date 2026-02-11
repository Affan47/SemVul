gretl_matrix_kronecker_I (const gretl_matrix *A, int r,
			  gretl_matrix *K)
{
    double x, aij, bkl;
    int p, q;
    int i, j, k, l;
    int ioff, joff;
    int Ki, Kj;

    if (gretl_is_null_matrix(A)) {
	return E_DATA;
    }

    p = A->rows;
    q = A->cols;

    if (K->rows != p * r || K->cols != q * r) {
	return E_NONCONF;
    }

    for (i=0; i<p; i++) {
	ioff = i * r;
	for (j=0; j<q; j++) {

	    aij = gretl_matrix_get(A, i, j);
	    joff = j * r;
	    for (k=0; k<r; k++) {
		Ki = ioff + k;
		for (l=0; l<r; l++) {
		    bkl = (k == l)? 1 : 0;
		    Kj = joff + l;
		    x = aij * bkl;
		    if (x == -0.0) {
			x = 0.0;
		    }
		    gretl_matrix_set(K, Ki, Kj, x);
		}
	    }
	}
    }

    return 0;
}

gretl_matrix_QR_ols (const gretl_matrix *Y,
			 const gretl_matrix *X,
			 gretl_matrix *B,
			 gretl_matrix *E,
			 gretl_matrix **XTXi,
			 gretl_matrix **Qout)
{
    int g = Y->cols;
    int k = X->cols;
    int T = X->rows;
    gretl_matrix *Q = NULL;
    gretl_matrix *R = NULL;
    gretl_matrix *G = NULL;
    int err = 0;

    if (B->rows != k || B->cols != g) {
	err = E_NONCONF;
    } else if (Y->rows != T) {
	err = E_NONCONF;
    } else if (E != NULL && (E->cols != g || E->rows != T)) {
	err = E_NONCONF;
    } else if (k > T) {
	err = E_DF;
    }

    if (!err) {
	Q = gretl_matrix_copy(X);
	R = gretl_matrix_alloc(k, k);
	G = gretl_matrix_alloc(k, g);
	if (Q == NULL || R == NULL || G == NULL) {
	    err = E_ALLOC;
	}
    }

    if (!err) {
	err = QR_OLS_work(Q, R);
    }

    if (!err) {

	gretl_matrix_multiply_mod(Q, GRETL_MOD_TRANSPOSE,
				  Y, GRETL_MOD_NONE,
				  G, GRETL_MOD_NONE);
    }

    if (!err) {

	gretl_matrix_multiply(R, G, B);
    }

    if (!err && E != NULL) {

	int i, imax = E->rows * E->cols;

	gretl_matrix_multiply(X, B, E);
	for (i=0; i<imax; i++) {
	    E->val[i] = Y->val[i] - E->val[i];
	}
    }


    if (!err && XTXi != NULL) {
	*XTXi = gretl_matrix_alloc(k, k);

	if (*XTXi == NULL) {
	    err = E_ALLOC;
	} else {
	    gretl_matrix_multiply_mod(R, GRETL_MOD_NONE,
				      R, GRETL_MOD_TRANSPOSE,
				      *XTXi, GRETL_MOD_NONE);
	}
    }

    if (!err && Qout != NULL) {
	*Qout = Q;
    } else {
	gretl_matrix_free(Q);
    }

    gretl_matrix_free(R);
    gretl_matrix_free(G);

    return err;
}

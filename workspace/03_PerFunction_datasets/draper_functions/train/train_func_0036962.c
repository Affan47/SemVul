gretl_covariance_matrix_from_varlist (const int *list,
				      const DATASET *dset,
				      gretl_matrix **means,
				      int *errp)
{
    gretl_matrix *V;
    gretl_vector *xbar;
    int k = list[0];
    int t, i, j;
    double vv, x, y;
    int n, err = 0;

    V = gretl_matrix_alloc(k, k);
    xbar = gretl_vector_alloc(k);

    if (V == NULL || xbar == NULL) {
	err = E_ALLOC;
	goto bailout;
    }

    for (i=0; i<k && !err; i++) {
	xbar->val[i] = gretl_mean(dset->t1, dset->t2, dset->Z[list[i+1]]);
	if (na(xbar->val[i])) {
	    err = E_DATA;
	}
    }

    for (i=0; i<k && !err; i++) {
	for (j=i; j<k; j++) {
	    vv = 0.0;
	    n = 0;
	    for (t=dset->t1; t<=dset->t2; t++) {
		x = dset->Z[list[i+1]][t];
		y = dset->Z[list[j+1]][t];
		if (na(x) || na(y)) {
		    continue;
		}
		vv += (x - xbar->val[i]) * (y - xbar->val[j]);
		n++;
	    }
	    if (n < 2) {
		err = E_DATA;
		vv = NADBL;
	    } else {
		vv /= (n - 1);
	    }
	    gretl_matrix_set(V, i, j, vv);
	    gretl_matrix_set(V, j, i, vv);
	}
    }

 bailout:

    if (means != NULL && !err) {
	*means = xbar;
    } else {
	gretl_vector_free(xbar);
    }

    if (err) {
	gretl_matrix_free(V);
	V = NULL;
	if (errp != NULL) {
	    *errp = err;
	}
    }

    return V;
}

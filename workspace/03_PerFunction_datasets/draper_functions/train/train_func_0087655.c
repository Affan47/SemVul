gretl_SVD_invert_matrix (gretl_matrix *a)
{
    gretl_matrix *u = NULL;
    gretl_matrix *s = NULL;
    gretl_matrix *vt = NULL;
    double x;
    int i, j, n;
    int rank = 0;
    int err = 0;

    if (gretl_is_null_matrix(a)) {
	return E_DATA;
    }

    if (a->rows != a->cols) {
	err = E_NONCONF;
	goto bailout;
    }

    n = a->rows;


    err = gretl_matrix_SVD(a, &u, &s, &vt);

    if (!err) {
#if 1
	double smin = svd_smin(a);
#else
	double smin = SVD_SMIN;
#endif

	for (i=0; i<n; i++) {
	    if (s->val[i] > smin) {
		rank++;
	    } else {
		break;
	    }
	}

	if (rank < n) {
	    gretl_matrix *vt2;

	    fprintf(stderr, "gretl_SVD_invert_matrix: rank = %d (dim = %d)\n",
		    rank, n);
	    fputs("Warning: computing Moore-Penrose generalized inverse\n", stderr);

	    vt2 = gretl_matrix_alloc(rank, n);
	    if (vt2 == NULL) {
		err = E_ALLOC;
		goto bailout;
	    }
	    for (i=0; i<rank; i++) {
		for (j=0; j<n; j++) {
		    x = gretl_matrix_get(vt, i, j);
		    gretl_matrix_set(vt2, i, j, x);
		}
	    }
	    gretl_matrix_free(vt);
	    vt = vt2;
	    gretl_matrix_reuse(u, n, rank);
	}
    }

    if (!err) {

	for (j=0; j<rank; j++) {
	    for (i=0; i<n; i++) {
		x = gretl_matrix_get(u, i, j);
		gretl_matrix_set(u, i, j, x / s->val[j]);
	    }
	}
	err = gretl_matrix_multiply_mod(vt, GRETL_MOD_TRANSPOSE,
					u, GRETL_MOD_TRANSPOSE,
					a, GRETL_MOD_NONE);
    }

 bailout:

    gretl_matrix_free(u);
    gretl_matrix_free(s);
    gretl_matrix_free(vt);

    return err;
}

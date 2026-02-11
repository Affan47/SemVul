kalman_refresh_matrices (kalman *K, PRN *prn)
{
    const gretl_matrix **cptr[] = {
	&K->F, &K->A, &K->H, &K->Q, &K->R, &K->mu
    };
    int cross_update = 0;
    int i, err = 0;

    for (i=0; i<NMATCALLS && !err; i++) {
	if (matrix_is_varying(K, i)) {
	    *cptr[i] = kalman_update_matrix(K, i, prn, &err);
	    if (!err) {
		if (K->p > 0 && i >= K_Q) {
		    cross_update = 1;
		} else {
		    err = check_matrix_dims(K, *cptr[i], i);
		}
	    }
	    if (err) {
		fprintf(stderr, "kalman_refresh_matrices: err = %d at t = %d\n",
			err, K->t);
	    }
	}
    }

    if (!err && K->step != NULL) {

	if (K->step->F != NULL) {
	    load_to_vec(K->step->F, K->F, K->t);
	}
	if (K->step->H != NULL) {
	    load_to_vec(K->step->H, K->H, K->t);
	}
    }

    if (!err && cross_update) {

	err = kalman_update_crossinfo(K, UPDATE_STEP);
    }

    return err;
}

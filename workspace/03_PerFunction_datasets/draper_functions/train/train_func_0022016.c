gretl_VAR_get_impulse_response (GRETL_VAR *var,
				int targ, int shock,
				int periods, double alpha,
				const DATASET *dset,
				int *err)
{
    gretl_matrix *point = NULL;
    gretl_matrix *full = NULL;
    gretl_matrix *ret = NULL;
    int i;

    if (periods == 0) {
	if (dset != NULL) {
	    periods = default_VAR_horizon(dset);
	} else {
	    *err = E_DATA;
	    return NULL;
	}
    }

    if (alpha != 0 && (alpha < 0.01 || alpha > 0.6)) {
	*err = E_DATA;
    }

    point = gretl_VAR_get_point_responses(var, targ, shock, periods, err);

    if (dset == NULL || dset->Z == NULL || alpha == 0.0) {


	ret = point;
    } else if (point != NULL) {
	full = irf_bootstrap(var, targ, shock, periods,
			     alpha, dset, err);
	if (full != NULL) {
	    double p;

	    for (i=0; i<periods; i++) {
		p = gretl_matrix_get(point, i, 0);
		gretl_matrix_set(full, i, 0, p);
	    }
	}
	gretl_matrix_free(point);
	ret = full;
    }

    return ret;
}

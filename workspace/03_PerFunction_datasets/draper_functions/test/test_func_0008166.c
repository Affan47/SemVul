make_cluster_vals (MODEL *pmod, int cvar,
					const DATASET *dset,
					int *err)
{
    gretl_matrix *cvals = NULL;
    double ct, *cdata;
    int s, t;

    cdata = malloc(pmod->nobs * sizeof *cdata);

    if (cdata == NULL) {
	*err = E_ALLOC;
    } else {
	s = 0;
	for (t=pmod->t1; t<=pmod->t2 && !*err; t++) {
	    if (!model_missing(pmod, t)) {
		ct = dset->Z[cvar][t];
		if (na(ct)) {
		    *err = E_MISSDATA;
		} else {
		    cdata[s++] = ct;
		}
	    }
	}
    }

    if (!*err) {
	cvals = gretl_matrix_values(cdata, pmod->nobs, OPT_S, err);
	if (!*err && gretl_vector_get_length(cvals) < 2) {
	    gretl_matrix_free(cvals);
	    cvals = NULL;
	    *err = E_DATA;
	}
    }

    free(cdata);

    return cvals;
}

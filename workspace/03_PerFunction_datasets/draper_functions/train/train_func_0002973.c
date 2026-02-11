gretl_VAR_get_series (const GRETL_VAR *var, const DATASET *dset,
			      int idx, const char *key, int *err)
{
    double *x = NULL;
    const char *msel;
    int t, col = 0;

    if (var == NULL || idx != M_UHAT) {
	*err = E_BADSTAT;
	return NULL;
    }

    msel = strchr(key, '[');
    if (msel == NULL || sscanf(msel, "[,%d]", &col) != 1) {
	*err = E_PARSE;
    } else if (col <= 0 || col > var->neqns) {
	*err = E_DATA;
    }

    if (!*err) {
	x = malloc(dset->n * sizeof *x);
	if (x == NULL) {
	    *err = E_ALLOC;
	}
    }

    if (!*err) {
	const MODEL *pmod = var->models[col-1];

	if (pmod == NULL || pmod->full_n != dset->n) {
	    *err = E_DATA;
	    free(x);
	    x = NULL;
	} else {
	    for (t=0; t<dset->n; t++) {
		x[t] = pmod->uhat[t];
	    }
	}
    }

    return x;
}

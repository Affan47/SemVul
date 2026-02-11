equation_system_get_series (const equation_system *sys,
			    const DATASET *dset,
			    int idx, const char *key, int *err)
{
    const gretl_matrix *M = NULL;
    double *x = NULL;
    const char *msel;
    int t, col = 0;

    if (sys == NULL || (idx != M_UHAT && idx != M_YHAT)) {
	*err = E_BADSTAT;
	return NULL;
    }

    msel = strchr(key, '[');
    if (msel == NULL || sscanf(msel, "[,%d]", &col) != 1) {
	*err = E_PARSE;
    } else if (col <= 0 || col > sys->neqns) {
	*err = E_DATA;
    }

    if (!*err) {
	M = (idx == M_UHAT)? sys->E : sys->yhat;
	if (M == NULL) {
	    *err = E_DATA;
	}
    }

    if (!*err) {
	x = malloc(dset->n * sizeof *x);
	if (x == NULL) {
	    *err = E_ALLOC;
	}
    }

    if (!*err) {
	int s = 0;

	col--;
	for (t=0; t<dset->n; t++) {
	    if (t < sys->t1 || t > sys->t2) {
		x[t] = NADBL;
	    } else {
		x[t] = gretl_matrix_get(M, s++, col);
	    }
	}
    }

    return x;
}

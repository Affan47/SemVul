data_array_from_model (const MODEL *pmod, double **Z, int missv)
{
    double **X;
    int nv = pmod->list[0];
    int offset = pmod->t1;
    int v, i;

    if (missv) {
	X = doubles_array_new(nv, pmod->nobs);
    } else {
	X = malloc(nv * sizeof *X);
    }

    if (X == NULL) return NULL;

    if (missv) {
	int t, s;

	for (t=0; t<pmod->nobs; t++) {
	    X[0][t] = 1.0;
	}

	for (i=1; i<nv; i++) {
	    v = (i == 1)? pmod->list[1] : pmod->list[i + 1];
	    s = 0;
	    for (t=pmod->t1; t<=pmod->t2; t++) {
		if (!na(pmod->uhat[t])) {
		    X[i][s++] = Z[v][t];
		}
	    }
	}
    } else {

	X[0] = Z[0] + offset;


	X[1] = Z[pmod->list[1]] + offset;


	for (i=2; i<nv; i++) {
	    v = pmod->list[i + 1];
	    X[i] = Z[v] + offset;
	}
    }

    return X;
}

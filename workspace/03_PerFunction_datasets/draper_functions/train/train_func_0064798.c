add_fit_resid_to_model (MODEL *pmod, nlspec *spec, double *uhat,
			const DATASET *dset, int perfect)
{
    int t, j = 0;

    if (perfect) {
	for (t=pmod->t1; t<=pmod->t2; t++) {
	    pmod->uhat[t] = 0.0;
	    pmod->yhat[t] = dset->Z[spec->dv][t];
	}
    } else {
	for (t=pmod->t1; t<=pmod->t2; t++) {
	    pmod->uhat[t] = uhat[j];
	    pmod->yhat[t] = dset->Z[spec->dv][t] - uhat[j];
	    j++;
	}
    }

    if (perfect || (spec->flags & NL_AUTOREG)) {
	pmod->rho = pmod->dw = NADBL;
    }
}

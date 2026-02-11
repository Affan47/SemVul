get_wls_stats (MODEL *pmod, const DATASET *dset)
{
    int dumwt = gretl_model_get_int(pmod, "wt_dummy");
    int t, wobs = pmod->nobs, yno = pmod->list[1];
    double x, dy, wmean = 0.0, wsum = 0.0;

    for (t=pmod->t1; t<=pmod->t2; t++) {
	if (model_missing(pmod, t)) {
	    continue;
	}
	if (dset->Z[pmod->nwt][t] == 0.0 && !dumwt) {
	    wobs--;
	    pmod->dfd -= 1;
	} else {
	    wmean += dset->Z[pmod->nwt][t] * dset->Z[yno][t];
	    wsum += dset->Z[pmod->nwt][t];
	}
    }

    wmean /= wsum;
    x = 0.0;

    for (t=pmod->t1; t<=pmod->t2; t++) {
	if (model_missing(pmod, t) || dset->Z[pmod->nwt][t] == 0.0) {
	    continue;
	}
	dy = dset->Z[yno][t] - wmean;
	x += dset->Z[pmod->nwt][t] * dy * dy;
    }

    pmod->fstt = ((x - pmod->ess) * pmod->dfd) / (pmod->dfn * pmod->ess);
    pmod->rsq = (1 - (pmod->ess / x));
    pmod->adjrsq = 1 - ((1 - pmod->rsq) * (pmod->nobs - 1)/pmod->dfd);
}

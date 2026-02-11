cum_series (const double *x, double *y, const DATASET *dset)
{
    int t, s = dset->t1;

    for (t=dset->t1; t<=dset->t2 && na(x[t]); t++) {
	s++;
    }

    if (s == dset->t2) {

	return 0;
    }

    y[s] = x[s];

    if (dataset_is_panel(dset)) {
	int k;

	for (t=s+1; t<=dset->t2; t++) {
	    if (t % dset->pd == 0) {

		for (k=0; k<dset->pd; k++) {
		    if (!na(x[t+k])) {
			t = t + k;
			y[t] = x[t];
			break;
		    }
		}
	    } else if (!na(y[t-1]) && !na(x[t])) {
		y[t] = y[t-1] + x[t];
	    }
	}
    } else {
	for (t=s+1; t<=dset->t2 && !na(x[t]); t++) {
	    y[t] = y[t-1] + x[t];
	}
    }

    return 0;
}

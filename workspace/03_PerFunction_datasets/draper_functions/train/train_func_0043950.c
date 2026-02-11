get_discdum (int v, double val, double *xvec,
			const DATASET *dset)
{
    double xt;
    int t;

    for (t=dset->t1; t<=dset->t2; t++) {
	xt = dset->Z[v][t];
	if (na(xt)) {
	    xvec[t] = NADBL;
	} else {
	    xvec[t] = (xt == val)? 1.0 : 0.0;
	}
    }

    return 0;
}

xcf_vec (const double *x, const double *y,
		       int p, const DATASET *dset,
		       int n, int *err)
{
    gretl_matrix *xcf = NULL;
    int t1, t2;
    int T, badvar = 0;

    if (p <= 0) {
	*err = E_DATA;
	return NULL;
    }

    if (dset != NULL) {
	int yt1, yt2;

	t1 = yt1 = dset->t1;
	t2 = yt2 = dset->t2;

	while (na(x[t1])) t1++;
	while (na(y[yt1])) yt1++;

	while (na(x[t2])) t2--;
	while (na(y[yt2])) yt2--;

	t1 = (yt1 > t1)? yt1 : t1;
	t2 = (yt2 < t2)? yt2 : t2;

	T = t2 - t1 + 1;
    } else {
	t1 = 0;
	t2 = n - 1;
	T = n;
    }

#if 0
    fprintf(stderr, "t1=%d, t2=%d, T=%d\n", t1, t2, T);
    fprintf(stderr, "x[t1]=%g, y[t1]=%g\n\n", x[t1], y[t1]);
#endif

    if (dset != NULL) {
	if (2 * p > T - dset->pd) {
	    *err = E_DATA;
	}
    } else if (2 * p > T) {
	*err = E_DATA;
    }

    if (!*err) {
	*err = xcf_data_check(x + t1, y + t1, T, &badvar);
	if (badvar) {
	    gretl_errmsg_sprintf(_("Argument %d is a constant"),
				 badvar);
	}
    }

    if (!*err) {
	xcf = real_xcf_vec(x + t1, y + t1, p, T, err);
    }

    return xcf;
}

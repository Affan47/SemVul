block_resample_series (const double *x, double *y, int blocklen,
			   const DATASET *dset)
{
    int t1 = dset->t1;
    int t2 = dset->t2;
    int *z = NULL;
    int m, rem, bt2, x0;
    int i, s, t, n;

    if (blocklen <= 0) {
	return E_DATA;
    }

    if (blocklen == 1) {
	return resample_series(x, y, dset);
    }

    series_adjust_sample(x, &t1, &t2);

    n = t2 - t1 + 1;

    m = n / blocklen;
    rem = n % blocklen;


    n = m + (rem > 0);


    bt2 = t2 - blocklen + 1;

    if (bt2 < t1) {
	return E_DATA;
    }

    z = malloc(n * sizeof *z);
    if (z == NULL) {
	return E_ALLOC;
    }


    gretl_rand_int_minmax(z, n, t1, bt2);


    t = t1;
    for (i=0; i<n; i++) {
	x0 = z[i];
	for (s=0; s<blocklen; s++) {
	    if (t <= t2) {
		y[t++] = x[x0+s];
	    } else {
		break;
	    }
	}
    }

    free(z);

    return 0;
}

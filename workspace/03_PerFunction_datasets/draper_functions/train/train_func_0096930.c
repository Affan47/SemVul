bigmul1_normal(VALUE x, VALUE y)
{
    long xl = RBIGNUM_LEN(x), yl = RBIGNUM_LEN(y), i, j = xl + yl + 1;
    BDIGIT_DBL n = 0;
    VALUE z = bignew(j, RBIGNUM_SIGN(x)==RBIGNUM_SIGN(y));
    BDIGIT *xds, *yds, *zds;

    xds = BDIGITS(x);
    yds = BDIGITS(y);
    zds = BDIGITS(z);
    while (j--) zds[j] = 0;
    for (i = 0; i < xl; i++) {
	BDIGIT_DBL dd;
	dd = xds[i];
	if (dd == 0) continue;
	n = 0;
	for (j = 0; j < yl; j++) {
	    BDIGIT_DBL ee = n + (BDIGIT_DBL)dd * yds[j];
	    n = zds[i + j] + ee;
	    if (ee) zds[i + j] = BIGLO(n);
	    n = BIGDN(n);
	}
	if (n) {
	    zds[i + j] = (BDIGIT)n;
	}
    }
    rb_thread_check_ints();
    return z;
}

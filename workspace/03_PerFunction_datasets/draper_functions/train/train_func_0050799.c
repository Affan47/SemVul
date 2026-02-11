netlib_bessel_K (double v, double x, int ize)
{
    int nb, ncalc;
    double *bk;

    if (isnan(x) || isnan(v)) {
	return x + v;
    }

    if (x < 0) {
	mtherr("netlib_bessel_K", CEPHES_DOMAIN);
	return NAN;
    }

    if (v < 0) {
	v = -v;
    }

    nb = 1 + (int) floor(v);
    v -= (nb - 1);

    bk = zero_dbl_array(nb);
    if (bk == NULL) {
	return NAN;
    }

    x = K_bessel(x, v, nb, ize, bk, &ncalc);

    if (ncalc != nb) {
	if (ncalc < 0) {
	    mtherr("netlib_bessel_K", CEPHES_TLOSS);
	    x = NAN;
	} else {
	    mtherr("netlib_bessel_K", CEPHES_PLOSS);
	}
    }

    free(bk);

    return x;
}

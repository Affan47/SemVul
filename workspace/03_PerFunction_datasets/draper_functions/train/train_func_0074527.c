bessel_i(double x, double alpha, double expo)
{
    long nb, ncalc, ize;
    double na, *bi;
#ifndef MATHLIB_STANDALONE
    const void *vmax;
#endif

#ifdef IEEE_754

    if (ISNAN(x) || ISNAN(alpha)) return x + alpha;
#endif
    if (x < 0) {
	ML_ERROR(ME_RANGE, "bessel_i");
	return ML_NAN;
    }
    ize = (long)expo;
    na = floor(alpha);
    if (alpha < 0) {


	return(bessel_i(x, -alpha, expo) +
	       ((alpha == na) ?  0 :
		bessel_k(x, -alpha, expo) *
		((ize == 1)? 2. : 2.*exp(-2.*x))/M_PI * sin(-M_PI * alpha)));
    }
    nb = 1 + (long)na;
    alpha -= (double)(nb-1);
#ifdef MATHLIB_STANDALONE
    bi = (double *) calloc(nb, sizeof(double));
    if (!bi) MATHLIB_ERROR("%s", _("bessel_i allocation error"));
#else
    vmax = vmaxget();
    bi = (double *) R_alloc((size_t) nb, sizeof(double));
#endif
    I_bessel(&x, &alpha, &nb, &ize, bi, &ncalc);
    if(ncalc != nb) {
	if(ncalc < 0)
	    MATHLIB_WARNING4(_("bessel_i(%g): ncalc (=%ld) != nb (=%ld); alpha=%g. Arg. out of range?\n"),
			     x, ncalc, nb, alpha);
	else
	    MATHLIB_WARNING2(_("bessel_i(%g,nu=%g): precision lost in result\n"),
			     x, alpha+(double)nb-1);
    }
    x = bi[nb-1];
#ifdef MATHLIB_STANDALONE
    free(bi);
#else
    vmaxset(vmax);
#endif
    return x;
}

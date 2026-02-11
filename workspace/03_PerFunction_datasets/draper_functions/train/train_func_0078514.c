bessel_i(gnm_float x, gnm_float alpha, gnm_float expo)
{
    long nb, ncalc, ize;
    gnm_float *bi;
#ifndef MATHLIB_STANDALONE
    char *vmax;
#endif

#ifdef IEEE_754

    if (gnm_isnan(x) || gnm_isnan(alpha)) return x + alpha;
#endif
    if (x < 0) {
	ML_ERROR(ME_RANGE);
	return gnm_nan;
    }
    ize = (long)expo;
    if (alpha < 0) {


	return(bessel_i(x, -alpha, expo) +
	       bessel_k(x, -alpha, expo) * ((ize == 1)? 2. : 2.*gnm_exp(-x))/M_PIgnum
	       * gnm_sinpi(-alpha));
    }
    nb = 1+ (long)gnm_floor(alpha);
    alpha -= (nb-1);
#ifdef MATHLIB_STANDALONE
    bi = (gnm_float *) calloc(nb, sizeof(gnm_float));
    if (!bi) MATHLIB_ERROR("%s", ("bessel_i allocation error"));
#else
    vmax = vmaxget();
    bi = (gnm_float *) R_alloc(nb, sizeof(gnm_float));
#endif
    I_bessel(&x, &alpha, &nb, &ize, bi, &ncalc);
    if(ncalc != nb) {
	if(ncalc < 0)
	    MATHLIB_WARNING4(("bessel_i(%" GNM_FORMAT_g "): ncalc (=%ld) != nb (=%ld); alpha=%" GNM_FORMAT_g ". Arg. out of range?\n"),
			     x, ncalc, nb, alpha);
	else
	    MATHLIB_WARNING2(("bessel_i(%" GNM_FORMAT_g ",nu=%" GNM_FORMAT_g "): precision lost in result\n"),
			     x, alpha+nb-1);
    }
    x = bi[nb-1];
#ifdef MATHLIB_STANDALONE
    free(bi);
#else
    vmaxset(vmax);
#endif
    return x;
}

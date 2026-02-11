pd_lower_cf (double y, double d)
{
    double f = 0, of;
    double i, c2, c3, c4,  a1, b1,  a2, b2;

#define	NEEDED_SCALE				\
	  (b2 > scalefactor) {			\
	    a1 /= scalefactor;			\
	    b1 /= scalefactor;			\
	    a2 /= scalefactor;			\
	    b2 /= scalefactor;			\
	}

#define max_it 200000

#ifdef DEBUG_p
    REprintf("pd_lower_cf(y=%.14g, d=%.14g)", y, d);
#endif
    if (y == 0 || (R_FINITE(y) && !R_FINITE(d)))
	return 0;

    if(fabs(y - 1) < fabs(d) * 1e-20) {
#ifdef DEBUG_p
	REprintf(" very small 'y' -> returning (y/d)\n");
#endif
	return (y/d);
    }

    c2 = y;
    c4 = d;

    a1 = 0; b1 = 1;
    a2 = y; b2 = d;

    while NEEDED_SCALE


    i = 0;
    while (i < max_it) {

	i++;	c2--;	c3 = i * c2;	c4 += 2;

	a1 = c4 * a2 + c3 * a1;
	b1 = c4 * b2 + c3 * b1;

	i++;	c2--;	c3 = i * c2;	c4 += 2;

	a2 = c4 * a1 + c3 * a2;
	b2 = c4 * b1 + c3 * b2;

	if NEEDED_SCALE

	if (b2 != 0) {
	    of = f;
	    f = a2 / b2;
#ifdef UP_TO_2009_11_07__NO_LONGER

	    if (fabs (f - of) <= DBL_EPSILON * fmax2(1., fabs(f))) { .. }
#endif

	    if (fabs(f - of) <= DBL_EPSILON * fabs(f)) {
#ifdef DEBUG_p
		REprintf(" %g iter.\n", i);
#endif
		return f;
	    }
	}
    }

    MATHLIB_WARNING(" ** NON-convergence in pgamma()'s pd_lower_cf() f= %g.\n",
		    f);
    return f;
}

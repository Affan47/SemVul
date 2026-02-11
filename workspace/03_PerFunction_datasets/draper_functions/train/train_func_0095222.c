pd_lower_series (gnm_float lambda, gnm_float y)
{
    gnm_float term = 1, sum = 0;

#ifdef DEBUG_p
    REprintf("pd_lower_series(lam=%.14" GNM_FORMAT_g ", y=%.14" GNM_FORMAT_g ") ...", lambda, y);
#endif
    while (y >= 1 && term > sum * GNM_EPSILON) {
	term *= y / lambda;
	sum += term;
	y--;
    }


#ifdef DEBUG_p
    REprintf(" done: term=%" GNM_FORMAT_g ", sum=%" GNM_FORMAT_g ", y= %" GNM_FORMAT_g "\n", term, sum, y);
#endif

    if (y != gnm_floor (y)) {


	gnm_float f;
#ifdef DEBUG_p
	REprintf(" y not int: add another term ");
#endif
	f = pd_lower_cf (y, lambda + 1 - y);
#ifdef DEBUG_p
	REprintf("  (= %.14" GNM_FORMAT_g ") * term = %.14" GNM_FORMAT_g " to sum %" GNM_FORMAT_g "\n", f, term * f, sum);
#endif
	sum += term * f;
    }

    return sum;
}

number_zerop(object x)
{
	switch (type_of(x)) {

	case t_fixnum:
		if (fix(x) == 0)
			return(1);
		else
			return(0);

	case t_bignum:
	case t_ratio:
		return(0);

	case t_shortfloat:
		if (sf(x) == 0.0)
			return(1);
		else
			return(0);

	case t_longfloat:
		if (lf(x) == 0.0)
			return(1);
		else
			return(0);

	case t_complex:
		return(number_zerop(x->cmp.cmp_real) &&
		       number_zerop(x->cmp.cmp_imag));

	default:
		FEwrong_type_argument(sLnumber, x);
		return(0);
	}
}

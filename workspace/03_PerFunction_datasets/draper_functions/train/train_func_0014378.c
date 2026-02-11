number_tan1(object x)
{
	double cos(double);

	switch (type_of(x)) {

	case t_fixnum:
	case t_bignum:
	case t_ratio:
		return(make_longfloat((longfloat)tan(number_to_double(x))));

	case t_shortfloat:
		return(make_shortfloat((shortfloat)tan((double)(sf(x)))));

	case t_longfloat:
		return(make_longfloat(tan(lf(x))));

	case t_complex:
	{
		object r;
		object x0, x1, x2;
		vs_mark;

		x0 = number_times(imag_two, x);
		vs_push(x0);
		x0 = number_exp(x0);
		vs_push(x0);
		x1 = number_minus(x0,small_fixnum(1));
		vs_push(x1);
		x2 = number_plus(x0,small_fixnum(1));
		vs_push(x2);
		x2 = number_times(x2,imag_unit);
		vs_push(x2);
		r = number_divide(x1, x2);

		vs_reset;
		return(r);
	}

	default:
		FEwrong_type_argument(sLnumber, x);
		return(Cnil);

	}
}

number_nlog(object x)
{
	double log(double);
	object r=Cnil, i=Cnil, a, p;
	vs_mark;

	if (type_of(x) == t_complex) {
		r = x->cmp.cmp_real;
		i = x->cmp.cmp_imag;
		goto COMPLEX;
	}
	if (number_zerop(x))
		FEerror("Zero is the logarithmic singularity.", 0);
	if (number_minusp(x)) {
		r = x;
		i = small_fixnum(0);
		goto COMPLEX;
	}
	switch (type_of(x)) {
	case t_fixnum:
	case t_bignum:
	case t_ratio:
		return(make_longfloat(log(number_to_double(x))));

	case t_shortfloat:
		return(make_shortfloat((shortfloat)log((double)(sf(x)))));

	case t_longfloat:
		return(make_longfloat(log(lf(x))));

	default:
		FEwrong_type_argument(sLnumber, x);
	}

COMPLEX:
	a = number_times(r, r);
	vs_push(a);
	p = number_times(i, i);
	vs_push(p);
	a = number_plus(a, p);
	vs_push(a);
	a = number_nlog(a);
	vs_push(a);
	a = number_divide(a, small_fixnum(2));
	vs_push(a);
	p = number_atan2(i, r);
	vs_push(p);
	x = make_complex(a, p);
	vs_reset;
	return(x);
}

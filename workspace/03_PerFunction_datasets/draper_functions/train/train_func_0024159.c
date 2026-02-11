nurat_s_convert(int argc, VALUE *argv, VALUE klass)
{
    VALUE a1, a2, backref;

    rb_scan_args(argc, argv, "11", &a1, &a2);

    if (NIL_P(a1) || (argc == 2 && NIL_P(a2)))
	rb_raise(rb_eTypeError, "can't convert nil into Rational");

    switch (TYPE(a1)) {
      case T_COMPLEX:
	if (k_exact_zero_p(RCOMPLEX(a1)->imag))
	    a1 = RCOMPLEX(a1)->real;
    }

    switch (TYPE(a2)) {
      case T_COMPLEX:
	if (k_exact_zero_p(RCOMPLEX(a2)->imag))
	    a2 = RCOMPLEX(a2)->real;
    }

    backref = rb_backref_get();
    rb_match_busy(backref);

    switch (TYPE(a1)) {
      case T_FIXNUM:
      case T_BIGNUM:
	break;
      case T_FLOAT:
	a1 = f_to_r(a1);
	break;
      case T_STRING:
	a1 = string_to_r_strict(a1);
	break;
    }

    switch (TYPE(a2)) {
      case T_FIXNUM:
      case T_BIGNUM:
	break;
      case T_FLOAT:
	a2 = f_to_r(a2);
	break;
      case T_STRING:
	a2 = string_to_r_strict(a2);
	break;
    }

    rb_backref_set(backref);

    switch (TYPE(a1)) {
      case T_RATIONAL:
	if (argc == 1 || (k_exact_one_p(a2)))
	    return a1;
    }

    if (argc == 1) {
	if (!(k_numeric_p(a1) && k_integer_p(a1)))
	    return rb_convert_type(a1, T_RATIONAL, "Rational", "to_r");
    }
    else {
	if ((k_numeric_p(a1) && k_numeric_p(a2)) &&
	    (!f_integer_p(a1) || !f_integer_p(a2)))
	    return f_div(a1, a2);
    }

    {
	VALUE argv2[2];
	argv2[0] = a1;
	argv2[1] = a2;
	return nurat_s_new(argc, argv2, klass);
    }
}

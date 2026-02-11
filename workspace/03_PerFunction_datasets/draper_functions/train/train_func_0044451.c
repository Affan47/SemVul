fix_pow(VALUE x, VALUE y)
{
    long a = FIX2LONG(x);

    if (FIXNUM_P(y)) {
	long b = FIX2LONG(y);

	if (b < 0)
	    return rb_funcall(rb_rational_raw1(x), rb_intern("**"), 1, y);

	if (b == 0) return INT2FIX(1);
	if (b == 1) return x;
	if (a == 0) {
	    if (b > 0) return INT2FIX(0);
	    return DBL2NUM(INFINITY);
	}
	if (a == 1) return INT2FIX(1);
	if (a == -1) {
	    if (b % 2 == 0)
		return INT2FIX(1);
	    else
		return INT2FIX(-1);
	}
	return int_pow(a, b);
    }
    switch (TYPE(y)) {
      case T_BIGNUM:

	if (rb_funcall(y, '<', 1, INT2FIX(0)))
	    return rb_funcall(rb_rational_raw1(x), rb_intern("**"), 1, y);

	if (a == 0) return INT2FIX(0);
	if (a == 1) return INT2FIX(1);
	if (a == -1) {
	    if (int_even_p(y)) return INT2FIX(1);
	    else return INT2FIX(-1);
	}
	x = rb_int2big(FIX2LONG(x));
	return rb_big_pow(x, y);
      case T_FLOAT:
	if (RFLOAT_VALUE(y) == 0.0) return DBL2NUM(1.0);
	if (a == 0) {
	    return DBL2NUM(RFLOAT_VALUE(y) < 0 ? INFINITY : 0.0);
	}
	if (a == 1) return DBL2NUM(1.0);
	{
	    double dy = RFLOAT_VALUE(y);
	    if (a < 0 && dy != round(dy))
		return rb_funcall(rb_complex_raw1(x), rb_intern("**"), 1, y);
	    return DBL2NUM(pow((double)a, dy));
	}
      default:
	return rb_num_coerce_bin(x, y, rb_intern("**"));
    }
}

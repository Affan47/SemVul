fix_cmp(VALUE x, VALUE y)
{
    if (x == y) return INT2FIX(0);
    if (FIXNUM_P(y)) {
	if (FIX2LONG(x) > FIX2LONG(y)) return INT2FIX(1);
	return INT2FIX(-1);
    }
    switch (TYPE(y)) {
      case T_BIGNUM:
	return rb_big_cmp(rb_int2big(FIX2LONG(x)), y);
      case T_FLOAT:
	return rb_dbl_cmp((double)FIX2LONG(x), RFLOAT_VALUE(y));
      default:
	return rb_num_coerce_cmp(x, y, rb_intern("<=>"));
    }
}

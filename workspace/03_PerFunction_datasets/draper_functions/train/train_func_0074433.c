f_cmp(VALUE x, VALUE y)
{
    if (FIXNUM_P(x) && FIXNUM_P(y)) {
	long c = FIX2LONG(x) - FIX2LONG(y);
	if (c > 0)
	    c = 1;
	else if (c < 0)
	    c = -1;
	return INT2FIX(c);
    }
    return rb_funcall(x, id_cmp, 1, y);
}

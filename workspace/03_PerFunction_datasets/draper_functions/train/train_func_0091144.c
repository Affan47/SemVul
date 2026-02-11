rb_big_aref(VALUE x, VALUE y)
{
    BDIGIT *xds;
    BDIGIT_DBL num;
    VALUE shift;
    long i, s1, s2;

    if (TYPE(y) == T_BIGNUM) {
	if (!RBIGNUM_SIGN(y))
	    return INT2FIX(0);
	bigtrunc(y);
	if (RBIGNUM_LEN(y) > DIGSPERLONG) {
	  out_of_range:
	    return RBIGNUM_SIGN(x) ? INT2FIX(0) : INT2FIX(1);
	}
	shift = big2ulong(y, "long", FALSE);
    }
    else {
	i = NUM2LONG(y);
	if (i < 0) return INT2FIX(0);
	shift = (VALUE)i;
    }
    s1 = shift/BITSPERDIG;
    s2 = shift%BITSPERDIG;

    if (s1 >= RBIGNUM_LEN(x)) goto out_of_range;
    if (!RBIGNUM_SIGN(x)) {
	xds = BDIGITS(x);
	i = 0; num = 1;
	while (num += ~xds[i], ++i <= s1) {
	    num = BIGDN(num);
	}
    }
    else {
	num = BDIGITS(x)[s1];
    }
    if (num & ((BDIGIT_DBL)1<<s2))
	return INT2FIX(1);
    return INT2FIX(0);
}

rb_int2inum(SIGNED_VALUE n)
{
    if (FIXABLE(n)) return LONG2FIX(n);
    return rb_int2big(n);
}

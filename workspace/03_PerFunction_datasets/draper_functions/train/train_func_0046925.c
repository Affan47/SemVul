Bignum_Fixnum_Divide (Object x, Object y) {
    Object big;
    register int xsize, i;
    register gran_t *xbuf, *zbuf;
    int fix = FIXNUM(y);
    int xminusp, yminusp = 0;
    register unsigned int rem;
    GC_Node;

    GC_Link (x);
    if (fix < 0) {
        fix = -fix;
        yminusp = 1;
    }
    if (fix > 0xFFFF) {
        big = Integer_To_Bignum (FIXNUM(y));
        GC_Unlink;
        return Bignum_Divide (x, big);
    }
    xsize = BIGNUM(x)->usize;
    big = Make_Uninitialized_Bignum (xsize);
    BIGNUM(big)->usize = xsize;
    xminusp = Truep (BIGNUM(x)->minusp);
    if (xminusp != yminusp)
        BIGNUM(big)->minusp = True;
    xbuf = BIGNUM(x)->data;
    zbuf = BIGNUM(big)->data;
    rem = 0;
    for (i = xsize; --i >= 0; ) {
        rem <<= 16;
        rem += xbuf[i];
        zbuf[i] = rem / fix;
        rem %= fix;
    }
    GC_Unlink;
    Bignum_Normalize_In_Place (BIGNUM(big));
    if (xminusp)
        rem = -(int)rem;
    return Cons (Reduce_Bignum (big), Make_Integer ((int)rem));
}

Bignum_Mantissa_Cmp (register struct S_Bignum *x,
                         register struct S_Bignum *y) {
    register unsigned int i = x->usize;
    if (i < y->usize)
        return -1;
    else if (i > y->usize)
        return 1;
    else {
        register gran_t *xbuf = x->data + i;
        register gran_t *ybuf = y->data + i;
        for ( ; i; --i) {
            register int n;
            if ((n = (int)*--xbuf - (int)*--ybuf))
                return n;
        }
        return 0;
    }
}

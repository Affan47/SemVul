diff(Bigint *a, Bigint *b)
{
    Bigint *c;
    int i, wa, wb;
    ULong *xa, *xae, *xb, *xbe, *xc;
#ifdef ULLong
    ULLong borrow, y;
#else
    ULong borrow, y;
    ULong z;
#endif

    i = cmp(a,b);
    if (!i) {
        c = Balloc(0);
        if (c == NULL)
            return NULL;
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    }
    else
        i = 0;
    c = Balloc(a->k);
    if (c == NULL)
        return NULL;
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
#ifdef ULLong
    do {
        y = (ULLong)*xa++ - *xb++ - borrow;
        borrow = y >> 32 & (ULong)1;
        *xc++ = (ULong)(y & FFFFFFFF);
    }
    while(xb < xbe);
    while(xa < xae) {
        y = *xa++ - borrow;
        borrow = y >> 32 & (ULong)1;
        *xc++ = (ULong)(y & FFFFFFFF);
    }
#else
    do {
        y = (*xa & 0xffff) - (*xb & 0xffff) - borrow;
        borrow = (y & 0x10000) >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) - borrow;
        borrow = (z & 0x10000) >> 16;
        Storeinc(xc, z, y);
    }
    while(xb < xbe);
    while(xa < xae) {
        y = (*xa & 0xffff) - borrow;
        borrow = (y & 0x10000) >> 16;
        z = (*xa++ >> 16) - borrow;
        borrow = (z & 0x10000) >> 16;
        Storeinc(xc, z, y);
    }
#endif
    while(!*--xc)
        wa--;
    c->wds = wa;
    return c;
}

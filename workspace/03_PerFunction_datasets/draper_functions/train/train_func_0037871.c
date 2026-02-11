multgf2ns(ptr)
truc *ptr;
{
    int n, m, sign, deg;
    word2 *x, *y;

    n = bigref(ptr,&x,&sign);
    m = bigref(ptr+1,&y,&sign);
    deg = gf2nField.deg;
    if(deg < bit_length(x,n) || deg < bit_length(y,m)) {
        error(timessym,"gf2nint factor too big",voidsym);
        return brkerr();
    }
    n = gf2polmult(x,n,y,m,AriBuf);
    n = gf2nmod(AriBuf,n);
    return mkgf2n(AriBuf,n);
}

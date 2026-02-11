divgf2ns(ptr)
truc *ptr;
{
    word2 *x, *y, *z;
    int n, m, sign, deg;

    n = bigref(ptr,&x,&sign);
    deg = gf2nField.deg;
    if(deg < bit_length(x,n)) {
        error(divfsym,"gf2nint argument too big",*ptr);
        return brkerr();
    }
    y = AriBuf;
    m = bigretr(ptr+1,y,&sign);
    if(deg < bit_length(y,m)) {
        error(divfsym,"gf2nint argument too big",ptr[1]);
        return brkerr();
    }
    z = y + m + 1;
    m = gf2ninverse(y,m,z,AriScratch);
    if(m == 0) {
        error(divfsym,err_div,voidsym);
        return brkerr();
    }
    n = gf2polmult(z,m,x,n,AriScratch);
    cpyarr(AriScratch,n,AriBuf);
    n = gf2nmod(AriBuf,n);
    return mkgf2n(AriBuf,n);
}

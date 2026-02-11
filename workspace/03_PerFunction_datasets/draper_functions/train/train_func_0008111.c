intretr(ptr)
truc *ptr;
{
    word2 *x;
    word4 u;
    long res;
    int n, sign;

    n = bigref(ptr,&x,&sign);
    if(n < 0 || n > 2 || (u = big2long(x,n)) >= 0x80000000)
        return(LONGERROR);
    res = u;
    return(sign ? -res : res);
}

Ffactorial()
{
    int n;
    word2 a;

    if(*FLAGPTR(argStkPtr) != fFIXNUM || *SIGNPTR(argStkPtr)) {
        error(factsym,err_pfix,*argStkPtr);
        return(brkerr());
    }
    a = *WORD2PTR(argStkPtr);
    if(a <= 1)
        return(constone);
    if(bitlen(a) > maxfltex/a + 1) {
        error(factsym,err_ovfl,voidsym);
        return(brkerr());
    }
    n = factorial(a,AriBuf);
    return(mkint(0,AriBuf,n));
}

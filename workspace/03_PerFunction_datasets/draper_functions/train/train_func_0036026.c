Fgf2Xprimtest()
{
    int n, sign, res;
    word2 *x;

    n = bigref(argStkPtr,&x,&sign);
    if (n == aERROR) {
        error(gf2Xprimsym,err_intt,argStkPtr[0]);
        return brkerr();
    }
    res = gf2polirred1(x,n,AriBuf,AriScratch);
    return (res ? true : false);
}

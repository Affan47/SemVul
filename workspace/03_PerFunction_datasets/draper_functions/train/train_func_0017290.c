sumintvec(argptr,len)
truc *argptr;
int len;
{
    word2 *y;
    int sign, cmp, n0, n1, m;

    n0 = n1 = 0;
    while(--len >= 0) {
        m = bigref(argptr,&y,&sign);
        if(sign)
            n1 = addarr(AriScratch,n1,y,m);
        else
            n0 = addarr(AriBuf,n0,y,m);
        argptr++;
    }
    cmp = cmparr(AriBuf,n0,AriScratch,n1);
    if(cmp < 0) {
        sign = MINUSBYTE;
        m = sub1arr(AriBuf,n0,AriScratch,n1);
    }
    else {
        sign = 0;
        m = subarr(AriBuf,n0,AriScratch,n1);
    }
    return(mkint(sign,AriBuf,m));
}

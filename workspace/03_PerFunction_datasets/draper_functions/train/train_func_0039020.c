prodfloatvec(argptr,len)
truc *argptr;
int len;
{
    numdata prod, temp;
    int prec;
    int n;

    prec = curFltPrec + 1;
    prod.digits = AriBuf;
    n = getnumtrunc(prec,argptr++,&prod);
    while(--len > 0 && n > 0) {
        refnumtrunc(prec,argptr++,&temp);
        n = multtrunc(prec,&prod,&temp,AriScratch);
    }
    if(n < 0) {
        error(prodsym,err_ovfl,voidsym);
        return(brkerr());
    }
    return(mkfloat(curFltPrec,&prod));
}

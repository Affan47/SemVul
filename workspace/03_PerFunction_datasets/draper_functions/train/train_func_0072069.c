sumfltvec(argptr,len)
truc *argptr;
int len;
{
    numdata accum, negsum, temp;
    numdata *nptr;
    int prec;
    int cmp, sign;

    prec = curFltPrec + 1;
    accum.digits = AriBuf;
    negsum.digits = AriScratch;
    temp.digits = AriScratch + aribufSize;
    accum.len = 0;
    accum.expo = MOSTNEGEX;
    negsum.len = 0;
    negsum.expo = MOSTNEGEX;
    while(--len >= 0) {
        if(!getnumalign(prec,argptr++,&temp))
            continue;
        sign = temp.sign;
        nptr = (sign ? &negsum : &accum);
        adjustoffs(nptr,&temp);
        nptr->len =
        addarr(nptr->digits,nptr->len,temp.digits,temp.len);
    }
    adjustoffs(&accum,&negsum);
    cmp = cmparr(accum.digits,accum.len,negsum.digits,negsum.len);
    if(cmp < 0) {
        accum.sign = MINUSBYTE;
        accum.len =
        sub1arr(accum.digits,accum.len,negsum.digits,negsum.len);
    }
    else {
        accum.sign = 0;
        accum.len =
        subarr(accum.digits,accum.len,negsum.digits,negsum.len);
    }
    return(mkfloat(curFltPrec,&accum));
}

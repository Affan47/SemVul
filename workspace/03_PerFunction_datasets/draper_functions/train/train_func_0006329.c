multints(ptr)
truc *ptr;
{
    word2 *x, *y;
    int n1, n2, n, sign, sign2;

    n1 = bigref(ptr,&x,&sign);
    n2 = bigref(ptr+1,&y,&sign2);
    if(n1 + n2 >= aribufSize)
        goto errexit;
    else if(!n1 || !n2)
        return(zero);
    n = multbig(x,n1,y,n2,AriBuf,AriScratch);
    sign = (sign == sign2 ? 0 : MINUSBYTE);
    return(mkint(sign,AriBuf,n));
  errexit:
    error(timessym,err_ovfl,voidsym);
    return(brkerr());
}

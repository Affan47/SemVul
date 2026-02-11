Fmodpower(argn)
int argn;
{
    word2 *x, *y, *z, *hilf;
    int n, n1, n2, n3;
    int sign1, sign2, sign3;

    if(chkints(modpowsym,argStkPtr-2,3) == aERROR)
        return(brkerr());

    x = AriScratch;
    hilf = AriScratch + aribufSize;

    n1 = bigretr(argStkPtr-2,x,&sign1);
    n2 = bigref(argStkPtr-1,&y,&sign2);
    n3 = bigref(argStkPtr,&z,&sign3);
    if(!n3) {
        error(modpowsym,err_div,voidsym);
        return(brkerr());
    }

    n = (n3 > n1 ? n3 : n1) + 3;
    if (n >= aribufSize/2 || n + aribufSize/3 >= scrbufSize/3) {
        error(modpowsym,err_ovfl,voidsym);
        return(brkerr());
    }
    if(sign2) {
        if(n1)
            n1 = modinverse(x,n1,z,n3,AriBuf,hilf);
        if(!n1) {
            error(modpowsym,err_div,voidsym);
            return(brkerr());
        }
        if(n2 == 1 && y[0] == 1) {
            n = n1;
            goto testsigns;
        }
        else {
            cpyarr(AriBuf,n1,x);
        }
    }
    n = modpower(x,n1,y,n2,z,n3,AriBuf,hilf);
    if(n == 0)
        return zero;

    if(n2 == 0)
        sign1 = 0;
    else if((*y & 1) == 0)
        sign1 = 0;
  testsigns:
    if(sign1 != sign3)
        n = sub1arr(AriBuf,n,z,n3);

    return(mkint(sign3,AriBuf,n));
}

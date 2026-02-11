is_square(N,len,root,hilf)
word2 *N, *root, *hilf;
int len;
{
    unsigned M = 15015;
    unsigned a;
    int k, rlen;

    if(len <= 0)
        return 0;
    if((N[0] & 1) == 0) {
        if((N[0] & 0x3) != 0)
            return 0;
    }
    else if((N[0] & 0x7) != 1)
        return 0;
    a = modarr(N,len,M);
    if(jac(a,13) == -1 || jac(a,11) == -1 || jac(a,7) == -1 ||
       jac(a,5) == -1 || jac(a,3) == -1)
        return 0;
    k = bigsqrt(N,len,root,&rlen,hilf);
    if(rlen == 0)
        return k;
    else
        return 0;
}

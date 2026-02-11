gf2polmodpow(x,n,y,m,f,flen,z,hilf)
word2 *x,*y,*z,*f,*hilf;
int n, m, flen;
{
    int N, k, exlen;

    if(m == 0) {
        z[0] = 1;
        return 1;
    }
    else if(n == 0)
        return 0;
    exlen = bit_length(y,m);
    cpyarr(x,n,z);
    N = n;
    for(k=exlen-2; k>=0; k--) {
        cpyarr(z,N,hilf);
        N = gf2polsquare(hilf,N,z);
        N = gf2polmod(z,N,f,flen);
        if(testbit(y,k)) {
            cpyarr(z,N,hilf);
            N = gf2polmult(hilf,N,x,n,z);
            N = gf2polmod(z,N,f,flen);
        }
    }
    return N;
}

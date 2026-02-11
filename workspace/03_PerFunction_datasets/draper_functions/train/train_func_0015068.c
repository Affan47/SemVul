jacobi(sign,x,n,y,m,hilf)
word2 *x, *y, *hilf;
int sign, n, m;
{
    int res;
    int m8, tlen;
    word2 *temp;

    res = (sign && (y[0] & 2) ? -1 : 1);
    while(n >= 1) {
        while((x[0] & 1) == 0) {
            n = shrarr(x,n,1);
            m8 = y[0] & 0x7;
            if(m8 == 3 || m8 == 5)
                res = -res;
        }
        if(*x == 1 && n == 1)
            return(res);
        temp = x;
        tlen = n;
        x = y;
        n = m;
        y = temp;
        m = tlen;
        if((x[0] & 2) && (y[0] & 2))
            res = -res;
        n = modbig(x,n,y,m,hilf);
    }
    return(0);
}

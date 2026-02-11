xorbitvec(x,n,y,m)
word2 *x,*y;
int n,m;
{
    if(n < m) {
        setarr(x+n,m-n,0);
        n = m;
    }
    xorarr(x,m,y);
    while(n > 0 && x[n-1] == 0)
        n--;
    return(n);
}

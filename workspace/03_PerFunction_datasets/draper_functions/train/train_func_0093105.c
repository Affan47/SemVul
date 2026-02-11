incarr(x,n,a)
word2 *x;
int n;
unsigned a;
{
    word4 u;
    int nn = n;

    while(a && --n >= 0) {
        u = *x;
        u += a;
        *x++ = u & 0xFFFF;
        a = (u >= 0x10000 ? 1 : 0);
    }
    if(a) {
        *x = a;
        nn++;
    }
    return(nn);
}

ipow(float x, int n)
{
    float xn;
    for (xn=1.0; n; n>>=1, x*=x)
 if (n&1)
     xn *= x;
    return xn;
}

notarr(x,n)
word2 *x;
int n;
{
    while(--n >= 0) {
        *x = ~*x;
        x++;
    }
}

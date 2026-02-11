bcd2int(x)
unsigned x;
{
    int i;
    word2 a[3];
    unsigned y;

    for(i=0; i<3; i++) {
        a[i] = (0x000F & x);
        x >>= 4;
    }
    y = x;
    for(i=2; i>=0; i--)
        y = y*10 + a[i];
    return(y);
}

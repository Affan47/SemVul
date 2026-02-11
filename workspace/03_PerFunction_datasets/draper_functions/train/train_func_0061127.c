swapbyte(void *dst,void *src,int toswap)
{
    int i,e;
    unsigned char *in = (unsigned char *) src;
    unsigned char *out = (unsigned char *) dst;

    for(i = 0,e=toswap;i < toswap;i++,e--)
    {
	out[i] = in[e-1];
    }
}

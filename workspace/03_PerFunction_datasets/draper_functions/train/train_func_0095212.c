block_copy(unsigned char *out, unsigned char *in,
                              int outstride, int instride, int sz)
{
    int rows = sz;
    while(rows--) {
        memcpy(out, in, sz);
        out += outstride;
        in += instride;
    }
}

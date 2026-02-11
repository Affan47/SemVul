pack_8to1(byte *outp, byte *inp, int w)
{
    int mask  = 128;
    int value = 0;
    for (; w > 0; w--)
    {
        if (*inp++)
            value |= mask;
        mask >>= 1;
        if (mask == 0) {
            mask = 128;
            *outp++= value;
            value = 0;
        }
    }
    if (mask != 128) {
        *outp++ = value;
    }
}

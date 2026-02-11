calc_binint(char *bytes, int nbytes)
{
    unsigned char *s = (unsigned char *)bytes;
    int i;
    long x = 0;

    for (i = 0; i < nbytes; i++) {
        x |= (long)s[i] << (8 * i);
    }


    if (SIZEOF_LONG > 4 && nbytes == 4) {
        x |= -(x & (1L << 31));
    }

    return x;
}

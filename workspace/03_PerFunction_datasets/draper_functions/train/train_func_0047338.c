mprEncode64(cchar *s)
{
    uint    shiftbuf;
    char    *buffer, *bp;
    ssize   len;
    int     i, j, shift;

    len = slen(s) * 2;
    if ((buffer = mprAlloc(len + 1)) == 0) {
        return NULL;
    }
    bp = buffer;
    *bp = '\0';
    while (*s) {
        shiftbuf = 0;
        for (j = 2; j >= 0 && *s; j--, s++) {
            shiftbuf |= ((*s & 0xff) << (j * 8));
        }
        shift = 18;
        for (i = ++j; i < 4 && bp < &buffer[len] ; i++) {
            *bp++ = encodeMap[(shiftbuf >> shift) & 0x3f];
            shift -= 6;
        }
        while (j-- > 0) {
            *bp++ = '=';
        }
        *bp = '\0';
    }
    return buffer;
}

compact(uchar *d, uchar *s)
{
    uchar *dest = d, *src = s, patt, *t, *end = s + _xsize;
    int i, n;
    while (src < end) {
        for (n = 0, t = src; t + 2 < end && !(*t == t[1] && *t == t[2]); t++)
            n++;

        while (n) {
            i = n > 126 ? 126 : n;
            n -= i;
            *dest++ = 0x80 | i;
            while (i--)
                *dest++ = *src++;
        }

        if (src == end)
            break;

        patt = *src++;
        for (n = 1; src < end && *src == patt; src++)
            n++;

        while (n) {
            i = n > 126 ? 126 : n;
            n -= i;
            *dest++ = i;
            *dest++ = patt;
        }
    }
    *dest++ = 0;
    return dest - d;
}

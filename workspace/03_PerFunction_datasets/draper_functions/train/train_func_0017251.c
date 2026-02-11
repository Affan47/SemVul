revstr(WC *dest, WC *src)
{
    int i;
    int ilast = WClen(src) - 1;

    for(i = ilast; i >= 0; i--)
        dest[ilast - i] = src[i];
    dest[ilast + 1] = '\0';

    return dest;
}

dotext(WKO_UCHAR *p, WKO_UCHAR *buf)
{
    WKO_USHORT us;

    if (*p == 0) {
            *buf = '\0';
            return 1;
    } else if (*p < 255) {
        strncpy(reinterpret_cast<char *>(buf), reinterpret_cast<char *>(p+1), *p);
        buf[*p]=0;
        return (*p)+1;
    } else {
        p += 1;
        p += doshort(p, &us);
        strncpy(reinterpret_cast<char *>(buf), reinterpret_cast<char *>(p), us);
        buf[us]=0;
        return (us)+3;
    }
}

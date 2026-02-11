ap_stripprefix(const char *bigstring,
                                        const char *prefix)
{
    const char *p1;

    if (*prefix == '\0')
        return bigstring;

    p1 = bigstring;
    while (*p1 && *prefix) {
        if (*p1++ != *prefix++)
            return bigstring;
    }
    if (*prefix == '\0')
        return p1;


    return bigstring;
}

getConverter (const char *from, const char **&to) {
    iconv_t cd = (iconv_t) -1;

    while (NULL != *to)
        if ((iconv_t) -1 != (cd = iconv_open(*to, from))) return cd;
        else ++to;

    return (iconv_t) -1;
}

set_multichar_encoding(const char *str)
{
#ifdef MULTI_CHARSET
    if (str && *str) {
        if (!strcasecmp(str, "utf8") || !strcasecmp(str, "ucs2")) {
            encoding_method = UCS2;
            multichar_decode = latin1;
        } else if (!strcasecmp(str, "sjis")) {
            encoding_method = SJIS;
            multichar_decode = sjis2jis;
        } else if (!strcasecmp(str, "eucj") || !strcasecmp(str, "euckr") || !strcasecmp(str, "gb")) {
            encoding_method = EUCJ;
            multichar_decode = eucj2jis;
        } else if (!strcasecmp(str, "big5")) {
            encoding_method = BIG5;
            multichar_decode = big5dummy;
        } else {
            encoding_method = LATIN1;
            multichar_decode = latin1;
        }
    }
#else
    return;
    str = NULL;
#endif
}

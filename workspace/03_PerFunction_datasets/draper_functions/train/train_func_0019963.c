Scm_SupportedCharacterEncodingP(const char *encoding)
{
    const char **cs = supportedCharacterEncodings;
    for (;*cs;cs++) {
        const char *p = *cs;
        const char *q = encoding;
        for (;*p && *q; p++, q++) {
            if (tolower(*p) != tolower(*q)) break;
        }
        if (*p == '\0' && *q == '\0') return TRUE;
    }
    return FALSE;
}

spdist(const char *s, const char *t)
{
    for (; apr_tolower(*s) == apr_tolower(*t); t++, s++) {
        if (*t == '\0') {
            return SP_MISCAPITALIZED;
        }
    }
    if (*s) {
        if (*t) {
            if (s[1] && t[1] && apr_tolower(*s) == apr_tolower(t[1])
                && apr_tolower(*t) == apr_tolower(s[1])
                && strcasecmp(s + 2, t + 2) == 0) {
                return SP_TRANSPOSITION;
            }
            if (strcasecmp(s + 1, t + 1) == 0) {
                return SP_SIMPLETYPO;
            }
        }
        if (strcasecmp(s + 1, t) == 0) {
            return SP_EXTRACHAR;
        }
    }
    if (*t && strcasecmp(s, t + 1) == 0) {
        return SP_MISSINGCHAR;
    }
    return SP_VERYDIFFERENT;
}

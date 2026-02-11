krb5int_utf8_strpbrk(const char *str, const char *set)
{
    const char *cset;
    krb5_ucs4 chstr, chset;

    for ( ; *str != '\0'; KRB5_UTF8_INCR(str)) {
        for (cset = set; *cset != '\0'; KRB5_UTF8_INCR(cset)) {
            if (krb5int_utf8_to_ucs4(str, &chstr) == 0
                && krb5int_utf8_to_ucs4(cset, &chset) == 0 && chstr == chset)
                return (char *)str;
        }
    }

    return NULL;
}

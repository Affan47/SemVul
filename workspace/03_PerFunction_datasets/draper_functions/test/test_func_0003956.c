skip_separators(const char *p, const char *end)
{
    while (p < end) {
        if (!SEPARATOR_P(*p)) break;
        p += SCM_CHAR_NFOLLOWS(*p)+1;
    }
    return p;
}

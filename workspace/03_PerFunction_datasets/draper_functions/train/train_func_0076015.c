match_until_eol(const char *p)
{
    if (!p) return 0;
    while (*p && *p != '\r')
        ++p;
    if (*p != '\r') return 0;
    ++p;
    return *p == '\n' ? ++p : 0;
}

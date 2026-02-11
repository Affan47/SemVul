match_one_of(const char *p, const char *s, char *result)
{
    if (!p) return 0;
    for (; *s; ++s)
        if (*p == *s) {
            *result = *p;
            return ++p;
        }
    return 0;
}

match_literal(const char *p, const char *s)
{
    if (!p) return 0;
    while (*p && *s && *p == *s) {
	++p;
	++s;
    }
    return *s ? 0 : p;
}

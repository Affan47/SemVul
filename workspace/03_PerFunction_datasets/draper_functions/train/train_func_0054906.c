cipoint(const char *s, size_t size)
{
    char *p;
    static const char post[] = "postmaster";
    static int plen = sizeof(post) - 1;

    if ((p = memchr(s, '@', size))== NULL)
	return NULL;
    if ((p - (s + 1) == plen) && !strncasecmp(post, s+1, plen)) {

	return s;
    }
    return p;
}

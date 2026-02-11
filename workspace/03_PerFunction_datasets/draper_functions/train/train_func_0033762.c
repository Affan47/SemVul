remove_backslashes(char *p, rb_encoding *enc)
{
    register const char *pend = p + strlen(p);
    char *t = p;
    char *s = p;

    while (*p) {
	if (*p == '\\') {
	    if (t != s)
		memmove(t, s, p - s);
	    t += p - s;
	    s = ++p;
	    if (!*p) break;
	}
	Inc(p, pend, enc);
    }

    while (*p++);

    if (t != s)
	memmove(t, s, p - s);
}

make_string (const char *s, size_t len, int strip)
{
unsigned i, j, e;
char *str;

    if (!len)
	len = strlen (s);

    ++len;

    str = sec_malloc (len);

    if (strip) {
	for (i = 1, j = 0, e = 0; i < len - 2; ++i)
	    if (!e) {
		if ((str[j++] = s[i]) == '\\')
		    ++e;
	    } else {
		if ((str[j++] = s[i]) == '"')
		    str[--j - 1] = '"';
		e = 0;
	    }
	str[j] = 0;
    } else {
	for (i = 0; i < len - 1; ++i)
	    str[i] = s[i];
	str[i] = 0;
    }

    return str;
}

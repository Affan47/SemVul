gretl_charpos (char c, const char *s)
{
    int i = 0;

    while (*s) {
	if (*s++ == c) {
	    return i;
	}
	i++;
    }

    return -1;
}

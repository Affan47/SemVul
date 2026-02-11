compress_spaces (char *s)
{
    int i = 0, inquote = 0;
    char *p, *q;

    if (s == NULL || *s == 0) {
	return s;
    }

    p = q = s;

    while (*s) {
	if (*s == '"' && (i == 0 || *(s-1) != '\\')) {
	    inquote = !inquote;
	}
	if (!inquote) {
	    if (*s == '\t') {
		*s = ' ';
	    }
	    if (*s == ' ') {
		p = s + 1;
		if (*p == 0) break;
		while (*p == ' ') p++;
		if (p - s > 1) {
		    memmove(s + 1, p, strlen(p) + 1);
		}
	    }
	}
	s++;
	i++;
    }

    return q;
}

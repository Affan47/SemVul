parseaddr_route(inp, routep)
char **inp;
char **routep;
{
    int c;
    char *src = *inp;
    char *dst;

    SKIPWHITESPACE(src);

    *routep = dst = src;

    for (;;) {
        c = *src++;
	if (isalnum(c) || c == '-' || c == '[' || c == ']' ||
	    c == ',' || c == '@') {
	    *dst++ = c;
	}
	else if (c == '.') {
	    if (dst > *routep && dst[-1] != '.') *dst++ = c;
	}
	else if (isspace(c) || c == '(') {
	    src--;
	    SKIPWHITESPACE(src);
	}
	else {
	    while (dst > *routep &&
		   (dst[-1] == '.' || dst[-1] == ',' || dst[-1] == '@')) dst--;
	    *dst = '\0';
	    *inp = src;
	    return c;
	}
    }
}

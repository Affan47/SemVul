imparse_astring(s, retval)
char **s;
char **retval;
{
    int c;
    char *d;
    int len = 0;
    int sawdigit = 0;

    switch (**s) {
    case '\0':
    case ' ':
    case '(':
    case ')':
    case '\r':
    case '\n':

	*retval = "";
	return EOF;

    default:


	return imparse_word(s, retval);

    case '\"':


	*retval = d = ++(*s);
	for (;;) {
	    c = *(*s)++;
	    if (c == '\\') {
		c = *(*s)++;
	    }
	    else if (c == '\"') {
		*d = '\0';
		return *(*s)++;
	    }
	    else if (c == '\0' || c == '\r' || c == '\n') {
		*retval = "";
		return EOF;
	    }
	    *d++ = c;
	}

    case '{':

        (*s)++;
        while (isdigit(c = *(*s)++)) {
            sawdigit = 1;
            len = len*10 + c - '0';
        }
        if (!sawdigit || c != '}' || *(*s)++ != '\r' || *(*s)++ != '\n') {
            *retval = "";
            return EOF;
        }
        *retval = *s;
        *s += len;
        c = **s;
        *(*s)++ = '\0';
        return c;
    }
}

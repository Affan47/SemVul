push_braces(ary, str, flags)
    VALUE ary;
    const char *str;
    int flags;
{
    char *buf = 0;
    char *b;
    const char *s, *p, *t;
    const char *lbrace, *rbrace;
    int nest = 0;
    int status = 0;

    s = p = str;
    lbrace = rbrace = 0;
    while (*p) {
	if (*p == '{') {
	    lbrace = p;
	    break;
	}
	p++;
    }
    while (*p) {
	if (*p == '{') nest++;
	if (*p == '}' && --nest == 0) {
	    rbrace = p;
	    break;
	}
	p++;
    }

    if (lbrace && rbrace) {
	int len = strlen(s);
	p = lbrace;
	while (*p != '}') {
	    t = p + 1;
	    for (p = t; *p!='}' && *p!=','; p++) {

		if (*p == '{') {
		    nest = 1;
		    while (*++p != '}' || --nest) {
			if (*p == '{') nest++;
		    }
		}
	    }
	    REALLOC_N(buf, char, len+1);
	    memcpy(buf, s, lbrace-s);
	    b = buf + (lbrace-s);
	    memcpy(b, t, p-t);
	    strcpy(b+(p-t), rbrace+1);
	    status = push_braces(ary, buf, flags);
	    if (status) break;
	}
    }
    else {
	status = push_globs(ary, str, flags);
    }
    xfree(buf);

    return status;
}

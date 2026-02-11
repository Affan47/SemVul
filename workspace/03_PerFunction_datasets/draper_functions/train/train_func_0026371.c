findNext(char *s, agxbuf* xb)
{
    char* t = s + 1;
    char c;
    int rc;

    if (*s == '<') {
	if ((*t == '!') && !strncmp(t + 1, "--", 2))
	    t = eatComment(t + 3);
	else
	    while (*t && (*t != '>'))
		t++;
	if (*t != '>') {
	    agerr(AGWARN, "Label closed before end of HTML element\n");
	    state.warn = 1;
	} else
	    t++;
    } else {
	t = s;
	while ((c = *t) && (c != '<')) {
	    if ((c == '&') && (*(t+1) != '#')) {
		t = scanEntity(t + 1, xb);
	    }
	    else {
		rc = agxbputc(xb, c);
		t++;
	    }
	}
    }
    return t;
}

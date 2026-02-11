cleanse_string(char *buf)
{
    char *stop, *p, *p2;

    p = buf;


    if (*buf != DQUOTE) {
	stop = G_index(buf, SPACE);
	if (stop == (char *)NULL)
	    return strlen(buf);
	else
	    return (int)(stop - buf);
    }
    else {


	if (*p == DQUOTE) {
	    while (*p != (char)NULL) {
		*p = *(p + 1);
		p++;
	    }
	    p = buf;
	    stop = G_index(p + 1, DQUOTE);
	    while (*(stop - 1) == BSLASH)
		stop = G_index(++stop, DQUOTE);
	}
    }

    p = buf;
    while ((p = G_index(p, BSLASH)) != (char *)NULL && p <= stop) {
	p2 = p + 1;
	if (*p2 != (char)NULL && (*p2 == DQUOTE || *p2 == BSLASH)) {
	    while (*p != (char)NULL) {
		*p = *(p + 1);
		p++;
	    }
	    stop--;
	}
	p = p2;
    }
    return (int)(stop - buf);
}

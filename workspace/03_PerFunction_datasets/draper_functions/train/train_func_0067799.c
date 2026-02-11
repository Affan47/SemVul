string_first(
    register Tcl_UniChar *string,
    int length,
    register char *pattern)

{
    Tcl_UniChar *s;
    char *p;
    int offset;
    register int consumed = 0;
    Tcl_UniChar ch1, ch2;
    Tcl_UniChar *bufend = string + length;

    while ((*string != 0) && (string < bufend)) {
	s = string;
	p = pattern;
        while ((*s) && (s < bufend)) {
	    ch1 = *s++;
            consumed++;
	    offset = TclUtfToUniChar(p, &ch2);
	    if (ch1 != ch2) {
		break;
	    }
	    p += offset;
	}
        if (*p == '\0') {
	    return string;
	}
        string++;
        consumed++;
    }
    return NULL;
}

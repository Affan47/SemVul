str_dup(const char *s)
{
    char *r;

    if (s == 0 || *s == '\0') {
	static char *emptystring;

	if (!emptystring) {
	    emptystring = (char *) mymalloc(1, M_STRING);
	    *emptystring = '\0';
	}
	addref(emptystring);
	return emptystring;
    } else {
	r = (char *) mymalloc(strlen(s) + 1, M_STRING);
	strcpy(r, s);
    }
    return r;
}

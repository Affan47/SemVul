GetValue(char *hdr, char *att, char **vsPtr, char **vePtr)
{
    char *s, *e;

    s = Ns_StrCaseFind(hdr, att);
    if (s == NULL) {
	return 0;
    }
    s += strlen(att);
    e = s;
    if (*s != '"' && *s != '\'') {

	while (*e && !isspace(UCHAR(*e))) {
	    ++e;
	}
    } else {

	++e;
	while (*e && *e != *s) {
	    ++e;
	}
	++s;
    }
    *vsPtr = s;
    *vePtr = e;
    return 1;
}

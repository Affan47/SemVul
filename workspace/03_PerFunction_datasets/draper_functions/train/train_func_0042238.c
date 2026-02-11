strnCopy(s,n)
String s;
Int n; {
    if (s) {
	char *t;
	if ((Int)strlen(s) < n)
	    n = strlen(s);
	if ((t=(char *)malloc(n+1))==0) {
	    ERRMSG(0) "String storage space exhausted"
	    EEND;
	}
	strncpy(t, s, n);
	t[n] = '\0';
	return t;
    }
    return NULL;
}

fakeCString(const wchar_t *u)
{
    char *s, *t;
    int len = uStrLen(u) + 1;
    t = s = (char*)malloc(len);
    while (*u) {
	if (*u == (wchar_t)0x2028)
	    *t = '\n';
	else if (*u == (wchar_t)0x2029)
	    *t = '\r';
	else
	    *t = (char)*u;
	u++; t++;
	}
    *t = 0;
    return s;
}

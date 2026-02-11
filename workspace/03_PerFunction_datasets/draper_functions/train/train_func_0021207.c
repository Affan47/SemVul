pkg_symbol(StrTable st, pkg_id pid)
{
    int len = 0;
    int i;
    char *p[3] = { NULL, NULL, NULL };
    static char *buf;

    for (i = 0; i < 3; i++) {
	if (pid.s[i] == 0) {
	    break;
	}
	p[i] = str_symbol(st, pid.s[i]);
	len += strlen(p[i]);
    }
    if (buf != NULL) {
	free(buf);
    }
    buf = (char *)malloc(len + 1);
    if (buf == NULL) {
	abort();
    }
    buf[0] = '\0';
    for (i = 0; i < 3; i++) {
	if (p[i]) {
	    strcat(buf, p[i]);
	} else {
	    break;
	}
    }
    return buf;
}

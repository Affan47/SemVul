fgetheader(FILE * f, const char *header)
{
    char *hdr, *p;
    size_t hlen;

    if (!header || !*header || header[(hlen = strlen(header))-1] != ':') {
	syslog(LOG_CRIT, "internal error in %s:%d", __FILE__, __LINE__);
	abort();
    }

    if (!f)
	return NULL;
    rewind(f);
    debug = 0;
    hdr = NULL;
    while ((p = getfoldedline(f, getaline)) && *p) {

	char *q = p;
	if ((strncasecmp(q, header, hlen) == 0)) {
	    q += hlen;
	    while (q && *q && isspace((unsigned char)*q))
		q++;
	    hdr = critstrdup(q, "fgetheader");
	    free(p); p = NULL;
	    break;
	}
	free(p); p = NULL;
    }
    if (p) free(p);
    debug = debugmode;
    rewind(f);
    return hdr;
}

ccp_printpkt(p, plen, printer, arg)
    u_char *p;
    int plen;
    void (*printer) __P((void *, char *, ...));
    void *arg;
{
    u_char *p0, *optend;
    int code, id, len;
    int optlen;

    p0 = p;
    if (plen < HEADERLEN)
	return 0;
    code = p[0];
    id = p[1];
    len = (p[2] << 8) + p[3];
    if (len < HEADERLEN || len > plen)
	return 0;

    if (code >= 1 && code <= sizeof(ccp_codenames) / sizeof(char *)
	&& ccp_codenames[code-1] != NULL)
	printer(arg, " %s", ccp_codenames[code-1]);
    else
	printer(arg, " code=0x%x", code);
    printer(arg, " id=0x%x", id);
    len -= HEADERLEN;
    p += HEADERLEN;

    switch (code) {
    case CONFREQ:
    case CONFACK:
    case CONFNAK:
    case CONFREJ:

	while (len >= 2) {
	    code = p[0];
	    optlen = p[1];
	    if (optlen < 2 || optlen > len)
		break;
	    printer(arg, " <");
	    len -= optlen;
	    optend = p + optlen;
	    switch (code) {
	    case CI_DEFLATE:
		if (optlen >= CILEN_DEFLATE) {
		    printer(arg, "deflate %d", DEFLATE_SIZE(p[2]));
		    if (DEFLATE_METHOD(p[2]) != DEFLATE_METHOD_VAL)
			printer(arg, " method %d", DEFLATE_METHOD(p[2]));
		    if (p[3] != DEFLATE_CHK_SEQUENCE)
			printer(arg, " check %d", p[3]);
		    p += CILEN_DEFLATE;
		}
		break;
	    case CI_BSD_COMPRESS:
		if (optlen >= CILEN_BSD_COMPRESS) {
		    printer(arg, "bsd v%d %d", BSD_VERSION(p[2]),
			    BSD_NBITS(p[2]));
		    p += CILEN_BSD_COMPRESS;
		}
		break;
	    case CI_PREDICTOR_1:
		if (optlen >= CILEN_PREDICTOR_1) {
		    printer(arg, "predictor 1");
		    p += CILEN_PREDICTOR_1;
		}
		break;
	    case CI_PREDICTOR_2:
		if (optlen >= CILEN_PREDICTOR_2) {
		    printer(arg, "predictor 2");
		    p += CILEN_PREDICTOR_2;
		}
		break;
	    }
	    while (p < optend)
		printer(arg, " %.2x", *p++);
	    printer(arg, ">");
	}
	break;
    }


    while (--len >= 0)
	printer(arg, " %.2x", *p++);

    return p - p0;
}

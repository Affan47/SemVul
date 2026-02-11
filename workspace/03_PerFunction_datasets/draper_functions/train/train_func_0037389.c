format_packet(p, len, printer, arg)
    u_char *p;
    int len;
    printer_func printer;
    void *arg;
{
    int i, n;
    u_short proto;
    struct protent *protp;

    if (len >= PPP_HDRLEN && p[0] == PPP_ALLSTATIONS && p[1] == PPP_UI) {
	p += 2;
	GETSHORT(proto, p);
	len -= PPP_HDRLEN;
	for (i = 0; (protp = protocols[i]) != NULL; ++i)
	    if (proto == protp->protocol)
		break;
	if (protp != NULL) {
	    printer(arg, "[%s", protp->name);
	    n = (*protp->printpkt)(p, len, printer, arg);
	    printer(arg, "]");
	    p += n;
	    len -= n;
	} else {
	    for (i = 0; (protp = protocols[i]) != NULL; ++i)
		if (proto == (protp->protocol & ~0x8000))
		    break;
	    if (protp != 0 && protp->data_name != 0) {
		printer(arg, "[%s data]", protp->data_name);
		if (len > 8)
		    printer(arg, "%.8B ...", p);
		else
		    printer(arg, "%.*B", len, p);
		len = 0;
	    } else
		printer(arg, "[proto=0x%x]", proto);
	}
    }

    if (len > 32)
	printer(arg, "%.32B ...", p);
    else
	printer(arg, "%.*B", len, p);
}

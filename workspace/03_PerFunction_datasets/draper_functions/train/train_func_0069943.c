fsm_rtermreq(fsm *f,int id,u_char *p,int len)
{
	char str[80];

    FSMDEBUG((LOG_INFO, "fsm_rtermreq(%s): Rcvd id %d.",
	      PROTO_NAME(f), id));

    switch (f->state) {
    case ACKRCVD:
    case ACKSENT:
	f->state = REQSENT;
	break;

    case OPENED:
		if (len > 0) {
			fmtmsg(str, sizeof(str), "%0.*v", len, p);
			syslog(LOG_INFO, "%s terminated by peer (%s)", PROTO_NAME(f), str);
		} else
			syslog(LOG_INFO, "%s terminated by peer", PROTO_NAME(f));
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);
	f->retransmits = 0;
	f->state = STOPPING;
	TIMEOUT(fsm_timeout, (caddr_t) f, f->timeouttime);
	break;
    }

    fsm_sdata(f, TERMACK, id, NULL, 0);
}

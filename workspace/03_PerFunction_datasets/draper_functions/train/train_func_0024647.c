lcp_rprotrej(f, inp, len)
    fsm *f;
    u_char *inp;
    int len;
{
    int i;
    struct protent *protp;
    u_short prot;

    LCPDEBUG((LOG_INFO, "lcp_rprotrej."));

    if (len < sizeof (u_short)) {
	LCPDEBUG((LOG_INFO,
		  "lcp_rprotrej: Rcvd short Protocol-Reject packet!"));
	return;
    }

    GETSHORT(prot, inp);

    LCPDEBUG((LOG_INFO,
	      "lcp_rprotrej: Rcvd Protocol-Reject packet for %x!",
	      prot));


    if( f->state != OPENED ){
	LCPDEBUG((LOG_INFO, "Protocol-Reject discarded: LCP in state %d",
		  f->state));
	return;
    }


    for (i = 0; (protp = protocols[i]) != NULL; ++i)
	if (protp->protocol == prot && protp->enabled_flag) {
	    (*protp->protrej)(f->unit);
	    return;
	}

    syslog(LOG_WARNING, "Protocol-Reject for unsupported protocol 0x%x",
	   prot);
}

fsm_sconfreq(fsm *f,int retransmit)
{
    u_char *outp;
    int cilen;

    if( f->state != REQSENT && f->state != ACKRCVD && f->state != ACKSENT ){

	if( f->callbacks->resetci )
	    (*f->callbacks->resetci)(f);
	f->nakloops = 0;
    }

    if( !retransmit ){

	f->retransmits = f->maxconfreqtransmits;
	f->reqid = ++f->id;
    }

    f->seen_ack = 0;


    outp = outpacket_buf + PPP_HDRLEN + HEADERLEN;
    if( f->callbacks->cilen && f->callbacks->addci ){
	cilen = (*f->callbacks->cilen)(f);
	if( cilen > lns[f->unit].peer_mru - HEADERLEN )
	    cilen = lns[f->unit].peer_mru - HEADERLEN;
	if (f->callbacks->addci)
	    (*f->callbacks->addci)(f, outp, &cilen);
    } else
	cilen = 0;


    fsm_sdata(f, CONFREQ, f->reqid, outp, cilen);


    --f->retransmits;
    TIMEOUT(fsm_timeout, (caddr_t) f, f->timeouttime);

    FSMDEBUG((LOG_INFO, "%s: sending Configure-Request, id %d",
	      PROTO_NAME(f), f->reqid));
}

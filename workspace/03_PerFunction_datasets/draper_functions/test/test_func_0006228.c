fsm_rtermack(f)
    fsm *f;
{
    FSMDEBUG((LOG_INFO, "fsm_rtermack(%s).", PROTO_NAME(f)));

    switch (f->state) {
    case CLOSING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = CLOSED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;
    case STOPPING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case ACKRCVD:
	f->state = REQSENT;
	break;

    case OPENED:
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);
	fsm_sconfreq(f, 0);
	break;
    }
}

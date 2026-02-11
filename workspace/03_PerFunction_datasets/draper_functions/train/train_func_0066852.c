fsm_lowerdown(f)
    fsm *f;
{
    switch( f->state ){
    case CLOSED:
	f->state = INITIAL;
	break;

    case STOPPED:
	f->state = STARTING;
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSING:
	f->state = INITIAL;
	UNTIMEOUT(fsm_timeout, f);
	break;

    case STOPPING:
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	f->state = STARTING;
	UNTIMEOUT(fsm_timeout, f);
	break;

    case OPENED:
	if( f->callbacks->down )
	    (*f->callbacks->down)(f);


#if 1
	f->state = CLOSED;
#else
	f->state = STARTING;
#endif

	break;

    default:
	FSMDEBUG(("%s: Down event in state %d!", PROTO_NAME(f), f->state));
    }
}

fsm_open(f)
    fsm *f;
{
    switch( f->state ){
    case INITIAL:
	f->state = STARTING;
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSED:
	if( f->flags & OPT_SILENT )
	    f->state = STOPPED;
	else {

	    fsm_sconfreq(f, 0);
	    f->state = REQSENT;
	}
	break;

    case CLOSING:
	f->state = STOPPING;

    case STOPPED:
    case OPENED:
	if( f->flags & OPT_RESTART ){
	    fsm_lowerdown(f);
	    fsm_lowerup(f);
	}
	break;
    }
}

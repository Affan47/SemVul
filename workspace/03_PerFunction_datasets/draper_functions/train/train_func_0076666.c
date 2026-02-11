tmr_mstimeout( struct timeval* nowP )
    {
    int h;
    int gotone;
    long msecs, m;
    register Timer* t;

    gotone = 0;
    msecs = 0;


    for ( h = 0; h < HASH_SIZE; ++h )
	{
	t = timers[h];
	if ( t != (Timer*) 0 )
	    {
	    m = ( t->time.tv_sec - nowP->tv_sec ) * 1000L +
		( t->time.tv_usec - nowP->tv_usec ) / 1000L;
	    if ( ! gotone )
		{
		msecs = m;
		gotone = 1;
		}
	    else if ( m < msecs )
		msecs = m;
	    }
	}
    if ( ! gotone )
	return INFTIM;
    if ( msecs <= 0 )
	msecs = 0;
    return msecs;
    }

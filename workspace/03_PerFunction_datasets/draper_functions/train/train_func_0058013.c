tmr_reset( struct timeval* nowP, Timer* t )
    {
    t->time = *nowP;
    t->time.tv_sec += t->msecs / 1000L;
    t->time.tv_usec += ( t->msecs % 1000L ) * 1000L;
    if ( t->time.tv_usec >= 1000000L )
	{
	t->time.tv_sec += t->time.tv_usec / 1000000L;
	t->time.tv_usec %= 1000000L;
	}
    l_resort( t );
    }

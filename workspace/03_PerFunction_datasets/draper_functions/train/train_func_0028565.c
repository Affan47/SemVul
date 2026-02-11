add_addr( char *name, char *host, FPING_SOCKADDR *ipaddr )
#endif
{
    HOST_ENTRY *p;
    int n, *i;

    p = ( HOST_ENTRY* )malloc( sizeof( HOST_ENTRY ) );
    if( !p )
        crash_and_burn( "can't allocate HOST_ENTRY" );

    memset( ( char* ) p, 0, sizeof( HOST_ENTRY ) );

    p->name = strdup(name);
    p->host = strdup(host);
#ifndef IPV6
    p->saddr.sin_family = AF_INET;
    p->saddr.sin_addr = ipaddr;
#else
    p->saddr.sin6_family = AF_INET6;
    (void)memcpy(&p->saddr, ipaddr, sizeof(FPING_SOCKADDR));
#endif
    p->timeout = timeout;
    p->running = 1;
    p->min_reply = 0;

    if( strlen( p->host ) > max_hostname_len )
        max_hostname_len = strlen( p->host );


    if( !loop_flag )
    {
        i = ( int* )malloc( trials * sizeof( int ) );
        if( !i )
            crash_and_burn( "can't allocate resp_times array" );

        for( n = 1; n < trials; n++ )
            i[n] = RESP_UNUSED;

        p->resp_times = i;

    }

#if defined( DEBUG ) || defined( _DEBUG )

    if( sent_times_flag )
    {
        i = ( int* )malloc( trials * sizeof( int ) );
        if( !i )
            crash_and_burn( "can't allocate sent_times array" );

        for( n = 1; n < trials; n++ )
            i[n] = RESP_UNUSED;

        p->sent_times = i;

    }
#endif


    p->ev_type = EV_TYPE_PING;
    p->ev_time.tv_sec  = 0;
    p->ev_time.tv_usec = 0;
    ev_enqueue(p);

    num_hosts++;

}

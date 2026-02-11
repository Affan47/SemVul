poll_init( int nfiles )
    {
    int i;

    pollfds = (struct pollfd*) malloc( sizeof(struct pollfd) * nfiles );
    poll_fdidx = (int*) malloc( sizeof(int) * nfiles );
    poll_rfdidx = (int*) malloc( sizeof(int) * nfiles );
    if ( pollfds == (struct pollfd*) 0 || poll_fdidx == (int*) 0 ||
	 poll_rfdidx == (int*) 0 )
	return -1;
    for ( i = 0; i < nfiles; ++i )
	pollfds[i].fd = poll_fdidx[i] = -1;
    return 0;
    }

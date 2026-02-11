SetSocketOptions( thread_Settings *inSettings ) {


    setsock_tcp_windowsize( inSettings->mSock, inSettings->mTCPWin,
                            (inSettings->mThreadMode == kMode_Client ? 1 : 0) );

    if ( isCongestionControl( inSettings ) ) {
#ifdef TCP_CONGESTION
	Socklen_t len = strlen( inSettings->mCongestion ) + 1;
	int rc = setsockopt( inSettings->mSock, IPPROTO_TCP, TCP_CONGESTION,
			     inSettings->mCongestion, len);
	if (rc == SOCKET_ERROR ) {
		fprintf(stderr, "Attempt to set '%s' congestion control failed: %s\n",
			inSettings->mCongestion, strerror(errno));
		exit(1);
	}
#else
	fprintf( stderr, "The -Z option is not available on this operating system\n");
#endif
    }


    if ( isMulticast( inSettings ) && ( inSettings->mTTL > 0 ) ) {
	int val = inSettings->mTTL;
#ifdef HAVE_MULTICAST
	if ( !SockAddr_isIPv6( &inSettings->peer ) ) {
	    int rc = setsockopt( inSettings->mSock, IPPROTO_IP, IP_MULTICAST_TTL,
		    (const void*) &val, (Socklen_t) sizeof(val));

	    WARN_errno( rc == SOCKET_ERROR, "multicast ttl" );
	}
#ifdef HAVE_IPV6_MULTICAST
	else {
	    int rc = setsockopt( inSettings->mSock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
		    (const void*) &val, (Socklen_t) sizeof(val));
	    WARN_errno( rc == SOCKET_ERROR, "multicast ttl" );
	}
#endif
#endif
    }


#ifdef IP_TOS


    if ( inSettings->mTOS > 0 ) {
        int  tos = inSettings->mTOS;
        Socklen_t len = sizeof(tos);
        int rc = setsockopt( inSettings->mSock, IPPROTO_IP, IP_TOS,
                             (char*) &tos, len );
        WARN_errno( rc == SOCKET_ERROR, "setsockopt IP_TOS" );
    }
#endif

    if ( !isUDP( inSettings ) ) {

        setsock_tcp_mss( inSettings->mSock, inSettings->mMSS );

#ifdef TCP_NODELAY


        if ( isNoDelay( inSettings ) ) {
            int nodelay = 1;
            Socklen_t len = sizeof(nodelay);
            int rc = setsockopt( inSettings->mSock, IPPROTO_TCP, TCP_NODELAY,
                                 (char*) &nodelay, len );
            WARN_errno( rc == SOCKET_ERROR, "setsockopt TCP_NODELAY" );
        }
#endif
    }
}

write_server( int sock, const char *data, size_t length )
{
    int nleft;

    nleft = length;
    while( nleft > 0 ) {
#ifdef _WIN32
        int nwritten;

        nwritten = send (sock, data, nleft, 0);
        if ( nwritten == SOCKET_ERROR ) {
	    log_info ("write failed: ec=%d\n", (int)WSAGetLastError ());
	    return G10ERR_NETWORK;
        }
#else
	int nwritten = write( sock, data, nleft );
	if( nwritten == -1 ) {
	    if( errno == EINTR )
		continue;
	    if( errno == EAGAIN ) {
		struct timeval tv;

		tv.tv_sec =  0;
		tv.tv_usec = 50000;
		select(0, NULL, NULL, NULL, &tv);
		continue;
	    }
	    log_info("write failed: %s\n", strerror(errno));
	    return G10ERR_NETWORK;
	}
#endif
	nleft -=nwritten;
	data += nwritten;
    }

    return 0;
}

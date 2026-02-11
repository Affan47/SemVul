receive_udp_packet( void *buf, int maxlen )
{
	struct sockaddr from;
	socklen_t fromlen;
	int result;

	fromlen = sizeof( from );

	result = recvfrom( listening_socket, buf, maxlen, 0, &from, &fromlen );

	if ( result == -1 ) {
		if ( errno != EINTR ) {
			printf( "recvfrom() returned an error which was not EINTR but %d\n", errno );
			exit( EXIT_FAILURE );
		}
	}

	return result;
}

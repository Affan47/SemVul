create_data_socket(int *dataFd, unsigned short *cbPort)
{

	struct sockaddr_in me;
#if defined(__linux__) || defined(__GNU__) || defined(__FreeBSD_kernel__)
	socklen_t       addrSize;
#else
	size_t          addrSize;
#endif
	int             bindResult;
	int             i;

	*dataFd = socket(AF_INET, SOCK_STREAM, 0);
	if (*dataFd < 0) {
		dc_errno = DESOCKET;
		return *dataFd;
	}

	memset((char *) &me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_addr.s_addr = htonl(INADDR_ANY);


	getPortRange();


	for( i = 0 ; i < callBackPortRange; i++) {

		*cbPort += i;
		me.sin_port = htons(*cbPort + i);
		addrSize = sizeof(me);
		bindResult = bind(*dataFd, (struct sockaddr *) & me, addrSize);
		if( bindResult == 0) break;

	}

	if (bindResult < 0) {
		dc_errno = DEBIND;
		system_close(*dataFd);
		*dataFd = -1;
		return -1;
	}


#if defined(__linux__) || defined(__GNU__) || defined(__FreeBSD_kernel__)
	getsockname(*dataFd, (struct sockaddr *) & me, (socklen_t *) &addrSize);
#else
	getsockname(*dataFd, (struct sockaddr *) & me, (int *) &addrSize);
#endif
	*cbPort = ntohs(me.sin_port);

	listen(*dataFd, 512);
	return 1;

}

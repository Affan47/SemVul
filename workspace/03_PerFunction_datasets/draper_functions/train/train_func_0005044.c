_mosquitto_socket_nonblock(int sock)
{
#ifndef WIN32
	int opt;

	opt = fcntl(sock, F_GETFL, 0);
	if(opt == -1){
		COMPAT_CLOSE(sock);
		return 1;
	}
	if(fcntl(sock, F_SETFL, opt | O_NONBLOCK) == -1){

		COMPAT_CLOSE(sock);
		return 1;
	}
#else
	opt = 1;
	if(ioctlsocket(sock, FIONBIO, &opt)){
		COMPAT_CLOSE(sock);
		return 1;
	}
#endif
	return 0;
}

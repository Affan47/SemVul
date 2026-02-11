psnet_init_tcp()
{
	SOCKADDR_IN sockaddr;

	TCP_socket = INVALID_SOCKET;

	TCP_socket = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( TCP_socket == (int)INVALID_SOCKET ) {
		Tcp_failure_code = WSAGetLastError();
		ml_printf("Error on TCP startup %d", Tcp_failure_code);
		return 0;
	}


	memset(&sockaddr,0,sizeof(SOCKADDR_IN));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = psnet_get_ip();
	sockaddr.sin_port = htons( Psnet_default_port );
	if ( bind(TCP_socket, (SOCKADDR*)&sockaddr, sizeof (sockaddr)) == SOCKET_ERROR) {
		Tcp_failure_code = WSAGetLastError();

		if (Tcp_failure_code == WSAEADDRINUSE) {
			ml_printf("TCP socket already in use!  Another instance running?  (Try using the \"-port %i\" cmdline option)", Psnet_default_port + 1);
		} else {
			ml_printf("Couldn't bind TCP socket (%d)! Invalidating TCP", Tcp_failure_code );
		}

		return 0;
	}


	psnet_socket_options( TCP_socket );
	Tcp_can_broadcast = Can_broadcast;


	return 1;
}

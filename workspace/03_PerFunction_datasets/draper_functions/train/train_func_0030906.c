start(){
	struct sockaddr_un sock_addr;
	size_t addrlen;
	int sock, n;

	memset( &sock_addr, 0, sizeof( sock_addr ) );
	sock_addr.sun_family = AF_UNIX;
	memcpy( sock_addr.sun_path, socket_path.c_str(), socket_path.size() );
	addrlen = sizeof( sock_addr.sun_family ) + socket_path.size();

	sock = socket( AF_UNIX, SOCK_STREAM, 0 );

	if( sock < 0 ){
		return false;
		}

	n = connect( sock, (struct sockaddr *)&sock_addr, addrlen );
	if( n < 0 ){
		return false;
		}

	conn = Connection( sock );

	connected = true;
	return true;
	}

init( size_t aport ){
	struct sockaddr_in6	server_addr;
	int fd, n, yes = 1;

	RequestHandler::init();

	port = aport;

	fd = socket( AF_INET6, SOCK_STREAM, 0 );

	if( fd < 0 ){
		throw std::string( "Socket error: ") + std::string( strerror( errno ) );
		return false;
		}

	setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) );

	memset( &server_addr, 0, sizeof( server_addr ) );

	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons( port );


	n = bind( fd, (struct sockaddr *) &server_addr, sizeof( server_addr ) );
	if( n < 0 ){
		perror("bind");
		throw std::string( "Bind error: ") + std::string( gai_strerror( n ) );
		return false;
		}

	n = listen( fd, 250 );
	if( n < 0 ){
		perror("Listen");
		throw std::string( "Listen error: ") + std::string( gai_strerror( n ) );
		return false;
		}

	master_socket = fd;

	connected = true;

	return true;
	}

createServerSocket()
{
  int i = 1;
  int newSocket;
  struct sockaddr_in s_in;
  struct servent *service;

  if ( ( newSocket = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
    log_error( "socket()" );
    return -1;
  }

  setsockopt( newSocket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof( i ) );


  if ( SocketPort == -1 ) {
    if ( ( service = getservbyname( "ksysguardd", "tcp" ) ) == NULL ) {


      SocketPort = PORT_NUMBER;
    } else
      SocketPort = htons( service->s_port );
  }

  memset( &s_in, 0, sizeof( struct sockaddr_in ) );
  s_in.sin_family = AF_INET;
  if ( BindToAllInterfaces )
      s_in.sin_addr.s_addr = htonl( INADDR_ANY );
  else
      s_in.sin_addr.s_addr = htonl( INADDR_LOOPBACK );
  s_in.sin_port = htons( SocketPort );

  if ( bind( newSocket, (struct sockaddr*)&s_in, sizeof( s_in ) ) < 0 ) {
    log_error( "Cannot bind to port %d", SocketPort );
    return -1;
  }

  if ( listen( newSocket, 5 ) < 0 ) {
    log_error( "listen()" );
    return -1;
  }

  return newSocket;
}

getListenSocket( uint16_t *desiredPort )
{
  int sock, t;
  struct sockaddr_in addr;

  if( ( sock = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {

    return -1;
  }


  t = 1;
  setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &t, sizeof( int ) );


  if( *desiredPort != 0 ) {

    addr.sin_family = AF_INET;
    addr.sin_port = htons( *desiredPort );
    addr.sin_addr.s_addr = htonl( INADDR_ANY );
    if( bind( sock, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) {

      return -1;
    }
  } else {

    t = 0;
    while( 1 ) {
      addr.sin_family = AF_INET;
      *desiredPort = ( random() % 64512 ) + 1024;
      addr.sin_port = htons( *desiredPort );
      addr.sin_addr.s_addr = htonl( INADDR_ANY );
      if( bind( sock, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) {

	if( t < NUM_PORT_CREATION_ATTEMPTS ) {

	  ++t;
	  continue;
	} else {

	  return -1;
	}
      }

      break;
    }
  }


  if( listen( sock, 8 ) < 0 ) {

    return -1;
  }

  return sock;
}

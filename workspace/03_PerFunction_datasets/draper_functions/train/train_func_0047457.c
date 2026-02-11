net_connect( int *fd, const char *host, int port )
{
#if defined(POLARSSL_HAVE_IPV6)
    int ret;
    struct addrinfo hints, *addr_list, *cur;
    char port_str[6];

    if( ( ret = net_prepare() ) != 0 )
        return( ret );


    memset( port_str, 0, sizeof( port_str ) );
    snprintf( port_str, sizeof( port_str ), "%d", port );


    memset( &hints, 0, sizeof( hints ) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if( getaddrinfo( host, port_str, &hints, &addr_list ) != 0 )
        return( POLARSSL_ERR_NET_UNKNOWN_HOST );


    ret = POLARSSL_ERR_NET_UNKNOWN_HOST;
    for( cur = addr_list; cur != NULL; cur = cur->ai_next )
    {
        *fd = (int) socket( cur->ai_family, cur->ai_socktype,
                            cur->ai_protocol );
        if( *fd < 0 )
        {
            ret = POLARSSL_ERR_NET_SOCKET_FAILED;
            continue;
        }

        if( connect( *fd, cur->ai_addr, cur->ai_addrlen ) == 0 )
        {
            ret = 0;
            break;
        }

        close( *fd );
        ret = POLARSSL_ERR_NET_CONNECT_FAILED;
    }

    freeaddrinfo( addr_list );

    return( ret );

#else


    int ret;
    struct sockaddr_in server_addr;
    struct hostent *server_host;

    if( ( ret = net_prepare() ) != 0 )
        return( ret );

    if( ( server_host = gethostbyname( host ) ) == NULL )
        return( POLARSSL_ERR_NET_UNKNOWN_HOST );

    if( ( *fd = (int) socket( AF_INET, SOCK_STREAM, IPPROTO_IP ) ) < 0 )
        return( POLARSSL_ERR_NET_SOCKET_FAILED );

    memcpy( (void *) &server_addr.sin_addr,
            (void *) server_host->h_addr,
                     server_host->h_length );

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = net_htons( port );

    if( connect( *fd, (struct sockaddr *) &server_addr,
                 sizeof( server_addr ) ) < 0 )
    {
        close( *fd );
        return( POLARSSL_ERR_NET_CONNECT_FAILED );
    }

    return( 0 );
#endif
}

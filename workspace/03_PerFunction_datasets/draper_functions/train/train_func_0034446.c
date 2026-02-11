ck_connect( ck_socket sock, const char * hostname, int port )
{
    int ret;
    struct hostent * host;

#ifdef __PLATFORM_WIN32__
    memset( &sock->sock_in, 0, sizeof(struct sockaddr_in) );
#else
    bzero( &sock->sock_in, sizeof(struct sockaddr_in) );
#endif

    sock->sock_in.sin_family = AF_INET;
    sock->sock_in.sin_port = htons( (unsigned short)abs(port) );

    host = gethostbyname( hostname );
    if( !host )
    {
        sock->sock_in.sin_addr.s_addr = inet_addr( hostname );
        if( sock->sock_in.sin_addr.s_addr == -1 )
            return FALSE;
    }
    else
    {
#ifdef __PLATFORM_WIN32__
        memcpy( (char *)&sock->sock_in.sin_addr, host->h_addr, host->h_length );
#else
        bcopy( host->h_addr, (char *)&sock->sock_in.sin_addr, host->h_length );
#endif
    }

    if( port < 0 )
        return TRUE;

    ret = ck_connect2( sock, (struct sockaddr *)&sock->sock_in,
        sizeof( struct sockaddr_in ) );

    return ( ret >= 0 );
}

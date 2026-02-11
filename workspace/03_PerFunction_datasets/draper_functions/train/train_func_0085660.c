get_host_by_address( struct in_addr in )
{
    struct hostent *h;
#ifndef IPV6
    h = gethostbyaddr( ( char* )&in, sizeof( struct in_addr ),AF_INET );
#else
    h = gethostbyaddr( ( char* )&in, sizeof( FPING_SOCKADDR ),AF_INET6 );
#endif

    if( h == NULL || h->h_name == NULL )
        return inet_ntoa( in );
    else
        return ( char* )h->h_name;

}

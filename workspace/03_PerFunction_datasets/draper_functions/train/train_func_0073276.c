us_net_convert_sockaddr_to_string( struct sockaddr const *addr, socklen_t addrlen, char *buf, size_t buflen )
{

    bool r = false;
    char hostbuf[512];
    char servbuf[512];

    *buf = 0;
    if ( addr && addrlen > 6 )
    {
#if US_ENABLE_RAW_ETHERNET
        if ( addr->sa_family == US_AF_LINK )
        {
            if ( addr->sa_family == US_AF_LINK )
            {
                uint8_t mac[6];
                memcpy( mac, us_sockaddr_dl_get_mac( addr ), 6 );
                snprintf( buf, buflen - 1, "[%02x:%02x:%02x:%02x:%02x:%02x]", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5] );
                r = true;
            }
        }
        else
#endif
        {
            int e = getnameinfo( addr,
                                 addrlen,
                                 hostbuf,
                                 sizeof( hostbuf ),
                                 servbuf,
                                 sizeof( servbuf ),
                                 NI_NUMERICHOST | NI_NUMERICSERV | NI_DGRAM );

            if ( e == 0 )
            {
                snprintf( buf, buflen - 1, "[%s]:%s", hostbuf, servbuf );
                r = true;
            }
            else
            {
                us_log_error( "getnameinfo sa_family %d error: %s", addr->sa_family, gai_strerror( e ) );
            }
        }
    }
    return r;
}

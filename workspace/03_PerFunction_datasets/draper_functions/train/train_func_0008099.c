rawnet_multi_send_data( struct us_socket_collection_s *self,
                                       void *context,
                                       int fd,
                                       struct sockaddr const *to_addr,
                                       socklen_t to_addrlen,
                                       uint8_t const *buf_,
                                       size_t len )
{

    us_socket_collection_rawnet_multi_t *self_multi = (us_socket_collection_rawnet_multi_t *)self;
    us_rawnet_context_t *rawnet = (us_rawnet_context_t *)context;
    uint8_t *buf = (uint8_t *)buf_;
    uint8_t const *destaddr = 0;
    int destination_if = -1;
    ssize_t r = -1;

    (void)self;
    (void)fd;


    if ( to_addr != 0 && to_addrlen >= sizeof( us_sockaddr_dl ) )
    {
        if ( to_addr->sa_family == US_AF_LINK )
        {
            destaddr = us_sockaddr_dl_get_mac( to_addr );
        }

        destination_if = us_rawnet_multi_route_find( self_multi->rawnet_multi, destaddr );
    }


    if ( destination_if == -1 || destination_if == rawnet->m_interface_id )
    {
        r = us_rawnet_send( rawnet, destaddr, buf, len );
    }
    return r;
}

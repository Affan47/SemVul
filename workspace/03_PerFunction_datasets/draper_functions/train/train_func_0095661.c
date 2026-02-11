rawnet_receive_data( struct us_socket_collection_s *self,
                                    void *context,
                                    int fd,
                                    uint64_t current_time_in_milliseconds,
                                    void *buf_,
                                    size_t buflen,
                                    struct sockaddr *from_addr,
                                    socklen_t *from_addrlen )
{
    ssize_t r = 0;
    us_rawnet_context_t *rawnet = (us_rawnet_context_t *)context;
    uint8_t *buf = (uint8_t *)buf_;
    uint8_t srcmac[6];
    uint8_t destmac[6];
    (void)self;
    (void)fd;
    r = us_rawnet_recv( rawnet, srcmac, destmac, buf, buflen );

    if ( r > 0 && from_addr != 0 && *from_addrlen >= sizeof( us_sockaddr_dl ) )
    {
        us_sockaddr_dl_set_mac( from_addr, srcmac );
        *from_addrlen = sizeof( us_sockaddr_dl );
    }

    return r;
}

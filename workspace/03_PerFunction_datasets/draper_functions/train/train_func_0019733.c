encode_sock( uint8_t * base,
                 size_t * idx,
                 const n2n_sock_t * sock )
{
    int retval=0;
    uint16_t f;

    switch (sock->family)
    {
    case AF_INET:
    {
        f = 0;
        retval += encode_uint16(base,idx,f);
        retval += encode_uint16(base,idx,sock->port);
        retval += encode_buf(base,idx,sock->addr.v4,IPV4_SIZE);
        break;
    }
    case AF_INET6:
    {
        f = 0x8000;
        retval += encode_uint16(base,idx,f);
        retval += encode_uint16(base,idx,sock->port);
        retval += encode_buf(base,idx,sock->addr.v6,IPV6_SIZE);
        break;
    }
    default:
        retval=-1;
    }

    return retval;
}

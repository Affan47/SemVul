encode_REGISTER_ACK( uint8_t * base,
                         size_t * idx,
                         const n2n_common_t * common,
                         const n2n_REGISTER_ACK_t * reg )
{
    int retval=0;
    retval += encode_common( base, idx, common );
    retval += encode_buf( base, idx, reg->cookie, N2N_COOKIE_SIZE );
    retval += encode_mac( base, idx, reg->dstMac );
    retval += encode_mac( base, idx, reg->srcMac );


    if ( 0 != reg->sock.family )
    {
        retval += encode_sock( base, idx, &(reg->sock) );
    }

    return retval;
}

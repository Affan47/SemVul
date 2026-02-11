encode_REGISTER_SUPER_ACK( uint8_t * base,
                               size_t * idx,
                               const n2n_common_t * common,
                               const n2n_REGISTER_SUPER_ACK_t * reg )
{
    int retval=0;
    retval += encode_common( base, idx, common );
    retval += encode_buf( base, idx, reg->cookie, N2N_COOKIE_SIZE );
    retval += encode_mac( base, idx, reg->edgeMac );
    retval += encode_uint16( base, idx, reg->lifetime );
    retval += encode_sock( base, idx, &(reg->sock) );
    retval += encode_uint8( base, idx, reg->num_sn );
    if ( reg->num_sn > 0 )
    {

        retval += encode_sock( base, idx, &(reg->sn_bak) );
    }

    return retval;
}

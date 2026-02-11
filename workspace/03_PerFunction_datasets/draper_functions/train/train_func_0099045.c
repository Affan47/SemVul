us_rawnet_recv(
    us_rawnet_context_t *self, uint8_t src_mac[6], uint8_t dest_mac[6], void *payload_buf, ssize_t payload_buf_max_size )
{
    ssize_t r = -1;
    ssize_t buf_len;
    uint8_t buf[2048];

    do
    {
        buf_len = recv( self->m_fd, buf, sizeof( buf ), 0 );
    } while ( buf_len < 0 && ( errno == EINTR ) );

    if ( buf_len >= 0 )
    {
        if ( src_mac )
        {
            memcpy( src_mac, &buf[6], 6 );
        }
        if ( dest_mac )
        {
            memcpy( dest_mac, &buf[0], 6 );
        }
        if ( payload_buf && ( payload_buf_max_size > buf_len - 14 ) )
        {
            memcpy( payload_buf, &buf[14], buf_len - 14 );
            r = buf_len - 14;
        }
    }
    return r;
}

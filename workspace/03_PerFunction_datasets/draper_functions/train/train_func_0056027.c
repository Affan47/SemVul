net_recv( void *ctx, unsigned char *buf, int len )
{
    int ret = read( *((int *) ctx), buf, len );

    if( len > 0 && ret == 0 )
        return( POLARSSL_ERR_NET_CONN_RESET );

    if( ret < 0 )
    {
        if( net_is_blocking() != 0 )
            return( POLARSSL_ERR_NET_TRY_AGAIN );

#if defined(_WIN32) || defined(_WIN32_WCE)
        if( WSAGetLastError() == WSAECONNRESET )
            return( POLARSSL_ERR_NET_CONN_RESET );
#else
        if( errno == EPIPE || errno == ECONNRESET )
            return( POLARSSL_ERR_NET_CONN_RESET );

        if( errno == EINTR )
            return( POLARSSL_ERR_NET_TRY_AGAIN );
#endif

        return( POLARSSL_ERR_NET_RECV_FAILED );
    }

    return( ret );
}

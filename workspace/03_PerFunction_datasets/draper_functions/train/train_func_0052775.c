ssl_free( ssl_context *ssl )
{
    SSL_DEBUG_MSG( 2, ( "=> free" ) );

    if( ssl->peer_cert != NULL )
    {
        x509_free( ssl->peer_cert );
        memset( ssl->peer_cert, 0, sizeof( x509_cert ) );
          free( ssl->peer_cert );
    }

    if( ssl->out_ctr != NULL )
    {
        memset( ssl->out_ctr, 0, SSL_BUFFER_LEN );
          free( ssl->out_ctr );
    }

    if( ssl->in_ctr != NULL )
    {
        memset( ssl->in_ctr, 0, SSL_BUFFER_LEN );
          free( ssl->in_ctr );
    }

#if defined(POLARSSL_DHM_C)
    dhm_free( &ssl->dhm_ctx );
#endif

    if ( ssl->hostname != NULL)
    {
        memset( ssl->hostname, 0, ssl->hostname_len );
        free( ssl->hostname );
        ssl->hostname_len = 0;
    }

    SSL_DEBUG_MSG( 2, ( "<= free" ) );


    memset( ssl, 0, sizeof( ssl_context ) );
}

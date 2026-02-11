ssl_handshake( ssl_context *ssl )
{
    int ret = POLARSSL_ERR_SSL_FEATURE_UNAVAILABLE;

    SSL_DEBUG_MSG( 2, ( "=> handshake" ) );

#if defined(POLARSSL_SSL_CLI_C)
    if( ssl->endpoint == SSL_IS_CLIENT )
        ret = ssl_handshake_client( ssl );
#endif

#if defined(POLARSSL_SSL_SRV_C)
    if( ssl->endpoint == SSL_IS_SERVER )
        ret = ssl_handshake_server( ssl );
#endif

    SSL_DEBUG_MSG( 2, ( "<= handshake" ) );

    return( ret );
}

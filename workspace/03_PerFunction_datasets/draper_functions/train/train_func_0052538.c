ssl_parse_certificate_verify( ssl_context *ssl )
{
    int ret;
    size_t n1, n2;
    unsigned char hash[36];

    SSL_DEBUG_MSG( 2, ( "=> parse certificate verify" ) );

    if( ssl->peer_cert == NULL )
    {
        SSL_DEBUG_MSG( 2, ( "<= skip parse certificate verify" ) );
        ssl->state++;
        return( 0 );
    }

    ssl_calc_verify( ssl, hash );

    if( ( ret = ssl_read_record( ssl ) ) != 0 )
    {
        SSL_DEBUG_RET( 1, "ssl_read_record", ret );
        return( ret );
    }

    ssl->state++;

    if( ssl->in_msgtype != SSL_MSG_HANDSHAKE )
    {
        SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( POLARSSL_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    if( ssl->in_msg[0] != SSL_HS_CERTIFICATE_VERIFY )
    {
        SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( POLARSSL_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    n1 = ssl->peer_cert->rsa.len;
    n2 = ( ssl->in_msg[4] << 8 ) | ssl->in_msg[5];

    if( n1 + 6 != ssl->in_hslen || n1 != n2 )
    {
        SSL_DEBUG_MSG( 1, ( "bad certificate verify message" ) );
        return( POLARSSL_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY );
    }

    ret = rsa_pkcs1_verify( &ssl->peer_cert->rsa, RSA_PUBLIC,
                            SIG_RSA_RAW, 36, hash, ssl->in_msg + 6 );
    if( ret != 0 )
    {
        SSL_DEBUG_RET( 1, "rsa_pkcs1_verify", ret );
        return( ret );
    }

    SSL_DEBUG_MSG( 2, ( "<= parse certificate verify" ) );

    return( 0 );
}

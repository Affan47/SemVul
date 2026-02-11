pk_write_key_pem( pk_context *key, unsigned char *buf, size_t size )
{
    int ret;
    unsigned char output_buf[4096];
    const char *begin, *end;
    size_t olen = 0;

    if( ( ret = pk_write_key_der( key, output_buf, sizeof(output_buf) ) ) < 0 )
        return( ret );

#if defined(POLARSSL_RSA_C)
    if( pk_get_type( key ) == POLARSSL_PK_RSA )
    {
        begin = PEM_BEGIN_PRIVATE_KEY_RSA;
        end = PEM_END_PRIVATE_KEY_RSA;
    }
    else
#endif
#if defined(POLARSSL_ECP_C)
    if( pk_get_type( key ) == POLARSSL_PK_ECKEY )
    {
        begin = PEM_BEGIN_PRIVATE_KEY_EC;
        end = PEM_END_PRIVATE_KEY_EC;
    }
    else
#endif
        return( POLARSSL_ERR_PK_FEATURE_UNAVAILABLE );

    if( ( ret = pem_write_buffer( begin, end,
                                  output_buf + sizeof(output_buf) - ret,
                                  ret, buf, size, &olen ) ) != 0 )
    {
        return( ret );
    }

    return( 0 );
}

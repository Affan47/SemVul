pkcs12_pbe( asn1_buf *pbe_params, int mode,
                cipher_type_t cipher_type, md_type_t md_type,
                const unsigned char *pwd,  size_t pwdlen,
                const unsigned char *data, size_t len,
                unsigned char *output )
{
    int ret, keylen = 0;
    unsigned char key[32];
    unsigned char iv[16];
    const cipher_info_t *cipher_info;
    cipher_context_t cipher_ctx;
    size_t olen = 0;

    cipher_info = cipher_info_from_type( cipher_type );
    if( cipher_info == NULL )
        return( POLARSSL_ERR_PKCS12_FEATURE_UNAVAILABLE );

    keylen = cipher_info->key_length / 8;

    if( ( ret = pkcs12_pbe_derive_key_iv( pbe_params, md_type, pwd, pwdlen,
                                          key, keylen,
                                          iv, cipher_info->iv_size ) ) != 0 )
    {
        return( ret );
    }

    if( ( ret = cipher_init_ctx( &cipher_ctx, cipher_info ) ) != 0 )
        goto exit;

    if( ( ret = cipher_setkey( &cipher_ctx, key, 8 * keylen, mode ) ) != 0 )
        goto exit;

    if( ( ret = cipher_set_iv( &cipher_ctx, iv, cipher_info->iv_size ) ) != 0 )
        goto exit;

    if( ( ret = cipher_reset( &cipher_ctx ) ) != 0 )
        goto exit;

    if( ( ret = cipher_update( &cipher_ctx, data, len,
                                output, &olen ) ) != 0 )
    {
        goto exit;
    }

    if( ( ret = cipher_finish( &cipher_ctx, output + olen, &olen ) ) != 0 )
        ret = POLARSSL_ERR_PKCS12_PASSWORD_MISMATCH;

exit:
    cipher_free_ctx( &cipher_ctx );

    return( ret );
}

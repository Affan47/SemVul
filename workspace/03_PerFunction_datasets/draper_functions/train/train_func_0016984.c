gcm_auth_decrypt( gcm_context *ctx,
                      size_t length,
                      const unsigned char *iv,
                      size_t iv_len,
                      const unsigned char *add,
                      size_t add_len,
                      const unsigned char *tag,
                      size_t tag_len,
                      const unsigned char *input,
                      unsigned char *output )
{
    unsigned char check_tag[16];

    gcm_crypt_and_tag( ctx, GCM_DECRYPT, length, iv, iv_len, add, add_len, input, output, tag_len, check_tag );

    if( memcmp( check_tag, tag, tag_len ) == 0 )
        return( 0 );

    memset( output, 0, length );

    return( POLARSSL_ERR_GCM_AUTH_FAILED );
}

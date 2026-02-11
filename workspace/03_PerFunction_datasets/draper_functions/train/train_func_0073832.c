blowfish_crypt_cfb64( blowfish_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[BLOWFISH_BLOCKSIZE],
                       const unsigned char *input,
                       unsigned char *output )
{
    int c;
    size_t n = *iv_off;

    if( mode == BLOWFISH_DECRYPT )
    {
        while( length-- )
        {
            if( n == 0 )
                blowfish_crypt_ecb( ctx, BLOWFISH_ENCRYPT, iv, iv );

            c = *input++;
            *output++ = (unsigned char)( c ^ iv[n] );
            iv[n] = (unsigned char) c;

            n = (n + 1) % BLOWFISH_BLOCKSIZE;
        }
    }
    else
    {
        while( length-- )
        {
            if( n == 0 )
                blowfish_crypt_ecb( ctx, BLOWFISH_ENCRYPT, iv, iv );

            iv[n] = *output++ = (unsigned char)( iv[n] ^ *input++ );

            n = (n + 1) % BLOWFISH_BLOCKSIZE;
        }
    }

    *iv_off = n;

    return( 0 );
}

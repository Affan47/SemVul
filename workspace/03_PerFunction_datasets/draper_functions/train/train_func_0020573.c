rsa_pkcs1_encrypt( rsa_context *ctx,
                       int (*f_rng)(void *),
                       void *p_rng,
                       int mode, int  ilen,
                       const unsigned char *input,
                       unsigned char *output )
{
    int nb_pad, olen;
    unsigned char *p = output;

    olen = ctx->len;

    switch( ctx->padding )
    {
        case RSA_PKCS_V15:

            if( ilen < 0 || olen < ilen + 11 || f_rng == NULL )
                return( POLARSSL_ERR_RSA_BAD_INPUT_DATA );

            nb_pad = olen - 3 - ilen;

            *p++ = 0;
            *p++ = RSA_CRYPT;

            while( nb_pad-- > 0 )
            {
                int rng_dl = 100;

                do {
                    *p = (unsigned char) f_rng( p_rng );
                } while( *p == 0 && --rng_dl );


                if( rng_dl == 0 )
                    return POLARSSL_ERR_RSA_RNG_FAILED;

                p++;
            }
            *p++ = 0;
            memcpy( p, input, ilen );
            break;

        default:

            return( POLARSSL_ERR_RSA_INVALID_PADDING );
    }

    return( ( mode == RSA_PUBLIC )
            ? rsa_public(  ctx, output, output )
            : rsa_private( ctx, output, output ) );
}

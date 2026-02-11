pkcs12_pbe_derive_key_iv( asn1_buf *pbe_params, md_type_t md_type,
                                     const unsigned char *pwd,  size_t pwdlen,
                                     unsigned char *key, size_t keylen,
                                     unsigned char *iv,  size_t ivlen )
{
    int ret, iterations;
    asn1_buf salt;
    size_t i;
    unsigned char unipwd[258];

    memset(&salt, 0, sizeof(asn1_buf));
    memset(&unipwd, 0, sizeof(unipwd));

    if( ( ret = pkcs12_parse_pbe_params( pbe_params, &salt, &iterations ) ) != 0 )
        return( ret );

    for(i = 0; i < pwdlen; i++)
        unipwd[i * 2 + 1] = pwd[i];

    if( ( ret = pkcs12_derivation( key, keylen, unipwd, pwdlen * 2 + 2,
                                   salt.p, salt.len, md_type,
                                   PKCS12_DERIVE_KEY, iterations ) ) != 0 )
    {
        return( ret );
    }

    if( iv == NULL || ivlen == 0 )
        return( 0 );

    if( ( ret = pkcs12_derivation( iv, ivlen, unipwd, pwdlen * 2 + 2,
                                   salt.p, salt.len, md_type,
                                   PKCS12_DERIVE_IV, iterations ) ) != 0 )
    {
        return( ret );
    }
    return( 0 );
}

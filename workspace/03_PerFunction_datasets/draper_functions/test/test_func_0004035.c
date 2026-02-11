pk_write_pubkey_der( pk_context *key, unsigned char *buf, size_t size )
{
    int ret;
    unsigned char *c;
    size_t len = 0, par_len = 0, oid_len;
    const char *oid;

    c = buf + size;

    ASN1_CHK_ADD( len, pk_write_pubkey( &c, buf, key ) );

    if( c - buf < 1 )
        return( POLARSSL_ERR_ASN1_BUF_TOO_SMALL );


    *--c = 0;
    len += 1;

    ASN1_CHK_ADD( len, asn1_write_len( &c, buf, len ) );
    ASN1_CHK_ADD( len, asn1_write_tag( &c, buf, ASN1_BIT_STRING ) );

    if( ( ret = oid_get_oid_by_pk_alg( pk_get_type( key ),
                                       &oid, &oid_len ) ) != 0 )
    {
        return( ret );
    }

#if defined(POLARSSL_ECP_C)
    if( pk_get_type( key ) == POLARSSL_PK_ECKEY )
    {
        ASN1_CHK_ADD( par_len, pk_write_ec_param( &c, buf, pk_ec( *key ) ) );
    }
#endif

    ASN1_CHK_ADD( len, asn1_write_algorithm_identifier( &c, buf, oid, oid_len,
                                                        par_len ) );

    ASN1_CHK_ADD( len, asn1_write_len( &c, buf, len ) );
    ASN1_CHK_ADD( len, asn1_write_tag( &c, buf, ASN1_CONSTRUCTED | ASN1_SEQUENCE ) );

    return( (int) len );
}

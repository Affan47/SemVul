asn1_write_null( unsigned char **p, unsigned char *start )
{
    int ret;
    size_t len = 0;


    ASN1_CHK_ADD( len, asn1_write_len( p, start, 0) );
    ASN1_CHK_ADD( len, asn1_write_tag( p, start, ASN1_NULL ) );

    return( len );
}

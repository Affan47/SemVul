asn1_write_int( unsigned char **p, unsigned char *start, int val )
{
    int ret;
    size_t len = 0;


    if( *p - start < 1 )
        return( POLARSSL_ERR_ASN1_BUF_TOO_SMALL );

    len += 1;
    *--(*p) = val;

    if ( val > 0 && **p & 0x80 )
    {
        if( *p - start < 1 )
            return( POLARSSL_ERR_ASN1_BUF_TOO_SMALL );

        *--(*p) = 0x00;
        len += 1;
    }

    ASN1_CHK_ADD( len, asn1_write_len( p, start, len ) );
    ASN1_CHK_ADD( len, asn1_write_tag( p, start, ASN1_INTEGER ) );

    return( (int) len );
}

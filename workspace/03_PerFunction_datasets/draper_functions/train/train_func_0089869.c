asn1_write_ia5_string( unsigned char **p, unsigned char *start,
                           const char *text, size_t text_len )
{
    int ret;
    size_t len = 0;

    ASN1_CHK_ADD( len, asn1_write_raw_buffer( p, start,
                  (const unsigned char *) text, text_len ) );

    ASN1_CHK_ADD( len, asn1_write_len( p, start, len ) );
    ASN1_CHK_ADD( len, asn1_write_tag( p, start, ASN1_IA5_STRING ) );

    return( (int) len );
}

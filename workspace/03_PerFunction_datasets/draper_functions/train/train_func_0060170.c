x509_get_subject_alt_name( unsigned char **p,
                                      const unsigned char *end,
                                      x509_sequence *subject_alt_name )
{
    int ret;
    size_t len, tag_len;
    asn1_buf *buf;
    unsigned char tag;
    asn1_sequence *cur = subject_alt_name;


    if( ( ret = asn1_get_tag( p, end, &len,
            ASN1_CONSTRUCTED | ASN1_SEQUENCE ) ) != 0 )
        return( POLARSSL_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p + len != end )
        return( POLARSSL_ERR_X509_INVALID_EXTENSIONS +
                POLARSSL_ERR_ASN1_LENGTH_MISMATCH );

    while( *p < end )
    {
        if( ( end - *p ) < 1 )
            return( POLARSSL_ERR_X509_INVALID_EXTENSIONS +
                    POLARSSL_ERR_ASN1_OUT_OF_DATA );

        tag = **p;
        (*p)++;
        if( ( ret = asn1_get_len( p, end, &tag_len ) ) != 0 )
            return( POLARSSL_ERR_X509_INVALID_EXTENSIONS + ret );

        if( ( tag & ASN1_CONTEXT_SPECIFIC ) != ASN1_CONTEXT_SPECIFIC )
            return( POLARSSL_ERR_X509_INVALID_EXTENSIONS +
                    POLARSSL_ERR_ASN1_UNEXPECTED_TAG );

        if( tag != ( ASN1_CONTEXT_SPECIFIC | 2 ) )
        {
            *p += tag_len;
            continue;
        }

        buf = &(cur->buf);
        buf->tag = tag;
        buf->p = *p;
        buf->len = tag_len;
        *p += buf->len;


        if (*p < end)
        {
            cur->next = (asn1_sequence *) polarssl_malloc(
                 sizeof( asn1_sequence ) );

            if( cur->next == NULL )
                return( POLARSSL_ERR_X509_INVALID_EXTENSIONS +
                        POLARSSL_ERR_ASN1_MALLOC_FAILED );

            memset( cur->next, 0, sizeof( asn1_sequence ) );
            cur = cur->next;
        }
    }


    cur->next = NULL;

    if( *p != end )
        return( POLARSSL_ERR_X509_INVALID_EXTENSIONS +
                POLARSSL_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

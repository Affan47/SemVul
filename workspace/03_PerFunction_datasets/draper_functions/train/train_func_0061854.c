x509_get_name( unsigned char **p,
                          const unsigned char *end,
                          x509_name *cur )
{
    int ret, len;
    const unsigned char *end2;
    x509_name *use;

    if( ( ret = asn1_get_tag( p, end, &len,
            ASN1_CONSTRUCTED | ASN1_SET ) ) != 0 )
        return( POLARSSL_ERR_X509_CERT_INVALID_NAME | ret );

    end2 = end;
    end  = *p + len;
    use = cur;

    do
    {
        if( ( ret = x509_get_attr_type_value( p, end, use ) ) != 0 )
            return( ret );

        if( *p != end )
        {
            use->next = (x509_name *) malloc(
                    sizeof( x509_name ) );

            if( use->next == NULL )
                return( 1 );

            memset( use->next, 0, sizeof( x509_name ) );

            use = use->next;
        }
    }
    while( *p != end );


    if( *p == end2 )
        return( 0 );

    cur->next = (x509_name *) malloc(
         sizeof( x509_name ) );

    if( cur->next == NULL )
        return( 1 );

    return( x509_get_name( p, end2, cur->next ) );
}

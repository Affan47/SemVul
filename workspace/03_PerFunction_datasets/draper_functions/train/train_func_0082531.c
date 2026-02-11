dhm_parse_dhm( dhm_context *dhm, const unsigned char *dhmin, size_t dhminlen )
{
    int ret;
    size_t len;
    unsigned char *p, *end;
#if defined(POLARSSL_PEM_PARSE_C)
    pem_context pem;

    pem_init( &pem );
    memset( dhm, 0, sizeof( dhm_context ) );

    ret = pem_read_buffer( &pem,
                           "-----BEGIN DH PARAMETERS-----",
                           "-----END DH PARAMETERS-----",
                           dhmin, NULL, 0, &dhminlen );

    if( ret == 0 )
    {


        dhminlen = pem.buflen;
    }
    else if( ret != POLARSSL_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
        goto exit;

    p = ( ret == 0 ) ? pem.buf : (unsigned char *) dhmin;
#else
    p = (unsigned char *) dhmin;
#endif
    end = p + dhminlen;


    if( ( ret = asn1_get_tag( &p, end, &len,
            ASN1_CONSTRUCTED | ASN1_SEQUENCE ) ) != 0 )
    {
        ret = POLARSSL_ERR_DHM_INVALID_FORMAT + ret;
        goto exit;
    }

    end = p + len;

    if( ( ret = asn1_get_mpi( &p, end, &dhm->P  ) ) != 0 ||
        ( ret = asn1_get_mpi( &p, end, &dhm->G ) ) != 0 )
    {
        ret = POLARSSL_ERR_DHM_INVALID_FORMAT + ret;
        goto exit;
    }

    if( p != end )
    {
        ret = POLARSSL_ERR_DHM_INVALID_FORMAT +
              POLARSSL_ERR_ASN1_LENGTH_MISMATCH;
        goto exit;
    }

    ret = 0;

exit:
#if defined(POLARSSL_PEM_PARSE_C)
    pem_free( &pem );
#endif
    if( ret != 0 )
        dhm_free( dhm );

    return( ret );
}

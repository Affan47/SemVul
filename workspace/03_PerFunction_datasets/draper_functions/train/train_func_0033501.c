asn1_get_len( unsigned char **p,
                         const unsigned char *end,
                         int *len )
{
    if( ( end - *p ) < 1 )
        return( POLARSSL_ERR_ASN1_OUT_OF_DATA );

    if( ( **p & 0x80 ) == 0 )
        *len = *(*p)++;
    else
    {
        switch( **p & 0x7F )
        {
        case 1:
            if( ( end - *p ) < 2 )
                return( POLARSSL_ERR_ASN1_OUT_OF_DATA );

            *len = (*p)[1];
            (*p) += 2;
            break;

        case 2:
            if( ( end - *p ) < 3 )
                return( POLARSSL_ERR_ASN1_OUT_OF_DATA );

            *len = ( (*p)[1] << 8 ) | (*p)[2];
            (*p) += 3;
            break;

        default:
            return( POLARSSL_ERR_ASN1_INVALID_LENGTH );
            break;
        }
    }

    if( *len > (int) ( end - *p ) )
        return( POLARSSL_ERR_ASN1_OUT_OF_DATA );

    return( 0 );
}

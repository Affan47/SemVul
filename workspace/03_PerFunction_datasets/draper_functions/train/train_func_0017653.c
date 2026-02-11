dhm_read_params( dhm_context *ctx,
                     unsigned char **p,
                     const unsigned char *end )
{
    int ret, n;

    memset( ctx, 0, sizeof( dhm_context ) );

    if( ( ret = dhm_read_bignum( &ctx->P,  p, end ) ) != 0 ||
        ( ret = dhm_read_bignum( &ctx->G,  p, end ) ) != 0 ||
        ( ret = dhm_read_bignum( &ctx->GY, p, end ) ) != 0 )
        return( ret );

    if( ( ret = dhm_check_range( &ctx->GY, &ctx->P ) ) != 0 )
        return( ret );

    ctx->len = mpi_size( &ctx->P );

    if( end - *p < 2 )
        return( POLARSSL_ERR_DHM_BAD_INPUT_DATA );

    n = ( (*p)[0] << 8 ) | (*p)[1];
    (*p) += 2;

    if( end != *p + n )
        return( POLARSSL_ERR_DHM_BAD_INPUT_DATA );

    return( 0 );
}

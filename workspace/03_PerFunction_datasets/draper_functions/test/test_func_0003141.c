dhm_read_public( dhm_context *ctx,
                     const unsigned char *input, size_t ilen )
{
    int ret;

    if( ctx == NULL || ilen < 1 || ilen > ctx->len )
        return( POLARSSL_ERR_DHM_BAD_INPUT_DATA );

    if( ( ret = mpi_read_binary( &ctx->GY, input, ilen ) ) != 0 )
        return( POLARSSL_ERR_DHM_READ_PUBLIC_FAILED + ret );

    return( 0 );
}

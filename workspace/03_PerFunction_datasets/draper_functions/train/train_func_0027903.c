dhm_make_params( dhm_context *ctx, int x_size,
                     unsigned char *output, size_t *olen,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    int ret, count = 0;
    size_t n1, n2, n3;
    unsigned char *p;

    if( mpi_cmp_int( &ctx->P, 0 ) == 0 )
        return( POLARSSL_ERR_DHM_BAD_INPUT_DATA );


    do
    {
        mpi_fill_random( &ctx->X, x_size, f_rng, p_rng );

        while( mpi_cmp_mpi( &ctx->X, &ctx->P ) >= 0 )
            mpi_shift_r( &ctx->X, 1 );

        if( count++ > 10 )
            return( POLARSSL_ERR_DHM_MAKE_PARAMS_FAILED );
    }
    while( dhm_check_range( &ctx->X, &ctx->P ) != 0 );


    MPI_CHK( mpi_exp_mod( &ctx->GX, &ctx->G, &ctx->X,
                          &ctx->P , &ctx->RP ) );

    if( ( ret = dhm_check_range( &ctx->GX, &ctx->P ) ) != 0 )
        return( ret );


#define DHM_MPI_EXPORT(X,n)                     \
    MPI_CHK( mpi_write_binary( X, p + 2, n ) ); \
    *p++ = (unsigned char)( n >> 8 );           \
    *p++ = (unsigned char)( n      ); p += n;

    n1 = mpi_size( &ctx->P  );
    n2 = mpi_size( &ctx->G  );
    n3 = mpi_size( &ctx->GX );

    p = output;
    DHM_MPI_EXPORT( &ctx->P , n1 );
    DHM_MPI_EXPORT( &ctx->G , n2 );
    DHM_MPI_EXPORT( &ctx->GX, n3 );

    *olen  = p - output;

    ctx->len = n1;

cleanup:

    if( ret != 0 )
        return( POLARSSL_ERR_DHM_MAKE_PARAMS_FAILED + ret );

    return( 0 );
}

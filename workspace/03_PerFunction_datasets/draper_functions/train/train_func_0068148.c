rsa_check_pubkey( rsa_context *ctx )
{
    if( ( ctx->N.p[0] & 1 ) == 0 ||
        ( ctx->E.p[0] & 1 ) == 0 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    if( mpi_msb( &ctx->N ) < 128 ||
        mpi_msb( &ctx->N ) > 4096 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    if( mpi_msb( &ctx->E ) < 2 ||
        mpi_msb( &ctx->E ) > 64 )
        return( POLARSSL_ERR_RSA_KEY_CHECK_FAILED );

    return( 0 );
}

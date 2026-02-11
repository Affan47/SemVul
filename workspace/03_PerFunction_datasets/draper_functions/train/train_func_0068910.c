ecdh_get_params( ecdh_context *ctx, const ecp_keypair *key,
                     ecdh_side side )
{
    int ret;

    if( ( ret = ecp_group_copy( &ctx->grp, &key->grp ) ) != 0 )
        return( ret );


    if( side == POLARSSL_ECDH_THEIRS )
        return( ecp_copy( &ctx->Qp, &key->Q ) );


    if( side != POLARSSL_ECDH_OURS )
        return( POLARSSL_ERR_ECP_BAD_INPUT_DATA );

    if( ( ret = ecp_copy( &ctx->Q, &key->Q ) ) != 0 ||
        ( ret = mpi_copy( &ctx->d, &key->d ) ) != 0 )
        return( ret );

    return( 0 );
}

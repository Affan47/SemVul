entropy_func( void *data, unsigned char *output, size_t len )
{
    int ret, count = 0, i, reached;
    entropy_context *ctx = (entropy_context *) data;
    unsigned char buf[ENTROPY_BLOCK_SIZE];

    if( len > ENTROPY_BLOCK_SIZE )
        return( POLARSSL_ERR_ENTROPY_SOURCE_FAILED );


    do
    {
        if( count++ > ENTROPY_MAX_LOOP )
            return( POLARSSL_ERR_ENTROPY_SOURCE_FAILED );

        if( ( ret = entropy_gather( ctx ) ) != 0 )
            return( ret );

        reached = 0;

        for( i = 0; i < ctx->source_count; i++ )
            if( ctx->source[i].size >= ctx->source[i].threshold )
                reached++;
    }
    while( reached != ctx->source_count );

    memset( buf, 0, ENTROPY_BLOCK_SIZE );

    sha4_finish( &ctx->accumulator, buf );


    sha4( buf, ENTROPY_BLOCK_SIZE, buf, 0 );


    memset( &ctx->accumulator, 0, sizeof( sha4_context ) );
    sha4_starts( &ctx->accumulator, 0 );
    sha4_update( &ctx->accumulator, buf, ENTROPY_BLOCK_SIZE );

    for( i = 0; i < ctx->source_count; i++ )
        ctx->source[i].size = 0;

    memcpy( output, buf, len );

    return( 0 );
}

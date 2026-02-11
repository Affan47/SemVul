xtea_setup( xtea_context *ctx, unsigned char key[16] )
{
    int i;

    memset(ctx, 0, sizeof(xtea_context));

    for( i = 0; i < 4; i++ )
    {
        GET_ULONG_BE( ctx->k[i], key, i << 2 );
    }
}

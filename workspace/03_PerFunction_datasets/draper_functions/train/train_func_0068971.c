sha4_finish( sha4_context *ctx, unsigned char output[64] )
{
    int last, padn;
    unsigned int64 high, low;
    unsigned char msglen[16];

    high = ( ctx->total[0] >> 61 )
         | ( ctx->total[1] <<  3 );
    low  = ( ctx->total[0] <<  3 );

    PUT_UINT64_BE( high, msglen, 0 );
    PUT_UINT64_BE( low,  msglen, 8 );

    last = (int)( ctx->total[0] & 0x7F );
    padn = ( last < 112 ) ? ( 112 - last ) : ( 240 - last );

    sha4_update( ctx, (unsigned char *) sha4_padding, padn );
    sha4_update( ctx, msglen, 16 );

    PUT_UINT64_BE( ctx->state[0], output,  0 );
    PUT_UINT64_BE( ctx->state[1], output,  8 );
    PUT_UINT64_BE( ctx->state[2], output, 16 );
    PUT_UINT64_BE( ctx->state[3], output, 24 );
    PUT_UINT64_BE( ctx->state[4], output, 32 );
    PUT_UINT64_BE( ctx->state[5], output, 40 );

    if( ctx->is384 == 0 )
    {
        PUT_UINT64_BE( ctx->state[6], output, 48 );
        PUT_UINT64_BE( ctx->state[7], output, 56 );
    }
}

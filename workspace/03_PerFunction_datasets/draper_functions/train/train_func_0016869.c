sha256_finish(ctx, digest)
    context_sha256_T *ctx;
    char_u	     digest[32];
{
    UINT32_T last, padn;
    UINT32_T high, low;
    char_u   msglen[8];

    high = (ctx->total[0] >> 29) | (ctx->total[1] <<  3);
    low  = (ctx->total[0] <<  3);

    PUT_UINT32(high, msglen, 0);
    PUT_UINT32(low,  msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    sha256_update(ctx, sha256_padding, padn);
    sha256_update(ctx, msglen, 8);

    PUT_UINT32(ctx->state[0], digest,  0);
    PUT_UINT32(ctx->state[1], digest,  4);
    PUT_UINT32(ctx->state[2], digest,  8);
    PUT_UINT32(ctx->state[3], digest, 12);
    PUT_UINT32(ctx->state[4], digest, 16);
    PUT_UINT32(ctx->state[5], digest, 20);
    PUT_UINT32(ctx->state[6], digest, 24);
    PUT_UINT32(ctx->state[7], digest, 28);
}

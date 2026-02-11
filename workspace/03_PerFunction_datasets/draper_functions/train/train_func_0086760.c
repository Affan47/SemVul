meh_finish_md5(MehMD5 ctx, unsigned char* output)
{
    uint32_t last, padlen;
    uint8_t msglen[8];

    U32TO8_LITTLE(msglen, ctx->total[0], 0);
    U32TO8_LITTLE(msglen, ctx->total[1], 4);

    last = (ctx->total[0] >> 3) & 0x3F;
    padlen = ( 56 > last)?
             ( 56 - last):
             (120 - last);

    meh_update_md5(ctx, meh_md5_padding, padlen);
    meh_update_md5(ctx, msglen, 8);

    U32TO8_LITTLE(output, ctx->state[0],  0);
    U32TO8_LITTLE(output, ctx->state[1],  4);
    U32TO8_LITTLE(output, ctx->state[2],  8);
    U32TO8_LITTLE(output, ctx->state[3], 12);
}

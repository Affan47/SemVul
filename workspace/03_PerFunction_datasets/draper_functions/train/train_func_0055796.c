av_md5_final(AVMD5 *ctx, uint8_t *dst){
    int i;
    uint64_t finalcount= le2me_64(ctx->len<<3);

    av_md5_update(ctx, "\200", 1);
    while((ctx->len & 63)!=56)
        av_md5_update(ctx, "", 1);

    av_md5_update(ctx, (uint8_t*)&finalcount, 8);

    for(i=0; i<4; i++)
        ((uint32_t*)dst)[i]= le2me_32(ctx->ABCD[3-i]);
}

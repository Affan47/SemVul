dnxhd_decode_macroblock(DNXHDContext *ctx, int x, int y)
{
    int dct_linesize_luma   = ctx->picture.linesize[0];
    int dct_linesize_chroma = ctx->picture.linesize[1];
    uint8_t *dest_y, *dest_u, *dest_v;
    int dct_offset;
    int qscale, i;

    qscale = get_bits(&ctx->gb, 11);
    skip_bits1(&ctx->gb);


    for (i = 0; i < 8; i++) {
        ctx->dsp.clear_block(ctx->blocks[i]);
        dnxhd_decode_dct_block(ctx, ctx->blocks[i], i, qscale);
    }

    if (ctx->picture.interlaced_frame) {
        dct_linesize_luma   <<= 1;
        dct_linesize_chroma <<= 1;
    }

    dest_y = ctx->picture.data[0] + ((y * dct_linesize_luma)   << 4) + (x << 4);
    dest_u = ctx->picture.data[1] + ((y * dct_linesize_chroma) << 4) + (x << 3);
    dest_v = ctx->picture.data[2] + ((y * dct_linesize_chroma) << 4) + (x << 3);

    if (ctx->cur_field) {
        dest_y += ctx->picture.linesize[0];
        dest_u += ctx->picture.linesize[1];
        dest_v += ctx->picture.linesize[2];
    }

    dct_offset = dct_linesize_luma << 3;
    ctx->dsp.idct_put(dest_y,                  dct_linesize_luma, ctx->blocks[0]);
    ctx->dsp.idct_put(dest_y + 8,              dct_linesize_luma, ctx->blocks[1]);
    ctx->dsp.idct_put(dest_y + dct_offset,     dct_linesize_luma, ctx->blocks[4]);
    ctx->dsp.idct_put(dest_y + dct_offset + 8, dct_linesize_luma, ctx->blocks[5]);

    if (!(ctx->avctx->flags & CODEC_FLAG_GRAY)) {
        dct_offset = dct_linesize_chroma << 3;
        ctx->dsp.idct_put(dest_u,              dct_linesize_chroma, ctx->blocks[2]);
        ctx->dsp.idct_put(dest_v,              dct_linesize_chroma, ctx->blocks[3]);
        ctx->dsp.idct_put(dest_u + dct_offset, dct_linesize_chroma, ctx->blocks[6]);
        ctx->dsp.idct_put(dest_v + dct_offset, dct_linesize_chroma, ctx->blocks[7]);
    }

    return 0;
}

sws_freeContext(struct SwsContext *ctx)
{
    if (!ctx)
        return;
    if ((ctx->resampling_ctx->iwidth != ctx->resampling_ctx->owidth) ||
        (ctx->resampling_ctx->iheight != ctx->resampling_ctx->oheight)) {
        img_resample_close(ctx->resampling_ctx);
    } else {
        av_free(ctx->resampling_ctx);
    }
    av_free(ctx);
}

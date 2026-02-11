Release(void *ctx)
{
    ContextInfo *ci;
    ci = (ContextInfo *) ctx;

    if (ctx) {
        sws_freeContext(ci->toRGB_convert_ctx);
        av_free(ctx);
    }
}

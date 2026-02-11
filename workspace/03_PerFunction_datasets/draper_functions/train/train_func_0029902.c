delete_state(DVBSubContext *ctx)
{
    DVBSubRegion *region;
    DVBSubCLUT *clut;

    while (ctx->region_list) {
        region = ctx->region_list;

        ctx->region_list = region->next;

        delete_region_display_list(ctx, region);
        if (region->pbuf)
            av_free(region->pbuf);

        av_free(region);
    }

    while (ctx->clut_list) {
        clut = ctx->clut_list;

        ctx->clut_list = clut->next;

        av_free(clut);
    }


    if (ctx->object_list)
        av_log(0, AV_LOG_ERROR, "Memory deallocation error!\n");
}

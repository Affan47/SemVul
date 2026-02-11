dav_validate_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err;

    if ((err = dav_validate_resource_state(ctx->w.pool, wres->resource,
                                           ctx->w.lockdb,
                                           ctx->if_header, ctx->flags,
                                           &ctx->work_buf, ctx->r)) == NULL) {

        return NULL;
    }


    if (ap_is_HTTP_SERVER_ERROR(err->status)
        || (*wres->resource->hooks->is_same_resource)(wres->resource,
                                                      ctx->w.root)) {

        return err;
    }


    dav_add_response(wres, err->status, NULL);

    return NULL;
}

dav_lock_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err;


    if ((*wres->resource->hooks->is_same_resource)(wres->resource,
                                                   ctx->w.root))
        return NULL;

    if ((err = (*ctx->w.lockdb->hooks->append_locks)(ctx->w.lockdb,
                                                     wres->resource, 1,
                                                     ctx->lock)) != NULL) {
        if (ap_is_HTTP_SERVER_ERROR(err->status)) {

            return err;
        }


        dav_add_response(wres, err->status, NULL);


    }

    return NULL;
}

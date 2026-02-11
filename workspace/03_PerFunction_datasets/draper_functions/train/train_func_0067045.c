dav_add_lock(request_rec *r,
                                      const dav_resource *resource,
                                      dav_lockdb *lockdb, dav_lock *lock,
                                      dav_response **response)
{
    dav_error *err;
    int depth = lock->depth;

    *response = NULL;


    if (!resource->collection) {
        depth = 0;
    }


    if ((err = (*lockdb->hooks->append_locks)(lockdb, resource, 0,
                                              lock)) != NULL) {

        return err;
    }

    if (depth > 0) {

        dav_walker_ctx ctx = { { 0 } };
        dav_response *multi_status;

        ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_AUTH;
        ctx.w.func = dav_lock_walker;
        ctx.w.walk_ctx = &ctx;
        ctx.w.pool = r->pool;
        ctx.w.root = resource;
        ctx.w.lockdb = lockdb;

        ctx.r = r;
        ctx.lock = lock;

        err = (*resource->hooks->walk)(&ctx.w, DAV_INFINITY, &multi_status);
        if (err != NULL) {

            return err;
        }

        if (multi_status != NULL) {

            *response = multi_status;
            return dav_new_error(r->pool, HTTP_MULTI_STATUS, 0, 0,
                                 "Error(s) occurred on resources during the "
                                 "addition of a depth lock.");
        }
    }

    return NULL;
}

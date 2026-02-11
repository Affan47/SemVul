dav_get_resource_state(request_rec *r,
                                        const dav_resource *resource)
{
    const dav_hooks_locks *hooks = DAV_GET_HOOKS_LOCKS(r);

    if (resource->exists)
        return DAV_RESOURCE_EXISTS;

    if (hooks != NULL) {
        dav_error *err;
        dav_lockdb *lockdb;
        int locks_present;


        if (r->path_info != NULL && *r->path_info != '\0') {
            return DAV_RESOURCE_NULL;
        }

        if ((err = (*hooks->open_lockdb)(r, 1, 1, &lockdb)) == NULL) {

            err = (*hooks->has_locks)(lockdb, resource, &locks_present);
            (*hooks->close_lockdb)(lockdb);
        }

        if (err != NULL) {


            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00623)
                          "Failed to query lock-null status for %s",
                          r->filename);

            return DAV_RESOURCE_ERROR;
        }

        if (locks_present)
            return DAV_RESOURCE_LOCK_NULL;
    }

    return DAV_RESOURCE_NULL;
}

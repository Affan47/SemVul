dav_fs_get_resource(
    request_rec *r,
    const char *root_dir,
    const char *label,
    int use_checked_in,
    dav_resource **result_resource)
{
    dav_resource_private *ctx;
    dav_resource *resource;
    char *s;
    char *filename;
    apr_size_t len;


    ctx = apr_pcalloc(r->pool, sizeof(*ctx));
    ctx->finfo = r->finfo;
    ctx->r = r;


    ctx->pool = r->pool;


#if 0

    filename = r->case_preserved_filename;
#else
    filename = r->filename;
#endif


    s = apr_pstrcat(r->pool, filename, r->path_info, NULL);


    len = strlen(s);
    if (len > 1 && s[len - 1] == '/') {
        s[len - 1] = '\0';
    }
    ctx->pathname = s;


    resource = apr_pcalloc(r->pool, sizeof(*resource));
    resource->type = DAV_RESOURCE_TYPE_REGULAR;
    resource->info = ctx;
    resource->hooks = &dav_hooks_repository_fs;
    resource->pool = r->pool;


    len = strlen(r->uri);
    if (len > 1 && r->uri[len - 1] == '/') {
        s = apr_pstrmemdup(r->pool, r->uri, len-1);
        resource->uri = s;
    }
    else {
        resource->uri = r->uri;
    }

    if (r->finfo.filetype != APR_NOFILE) {
        resource->exists = 1;
        resource->collection = r->finfo.filetype == APR_DIR;


        if (r->path_info != NULL && *r->path_info != '\0') {
            if (resource->collection) {

                if (*r->path_info != '/' || r->path_info[1] != '\0') {


                    resource->exists = 0;
                    resource->collection = 0;
                }
            }
            else
            {


                return dav_new_error(r->pool, HTTP_BAD_REQUEST, 0, 0,
                                     "The URL contains extraneous path "
                                     "components. The resource could not "
                                     "be identified.");
            }


            if (!resource->exists) {
                ctx->finfo.filetype = APR_NOFILE;
            }
        }
    }

    *result_resource = resource;
    return NULL;
}

apache2_temp_dir_set(apreq_handle_t *handle,
                                  const char *path)
{
    ap_filter_t *f = get_apreq_filter(handle);
    struct filter_ctx *ctx;

    if (f->ctx == NULL)
        apreq_filter_make_context(f);

    ctx = f->ctx;

    if (ctx->temp_dir == NULL && ctx->bytes_read == 0) {
        if (path != NULL)
            ctx->temp_dir = apr_pstrdup(handle->pool, path);
        return APR_SUCCESS;
    }

    return APREQ_ERROR_NOTEMPTY;
}

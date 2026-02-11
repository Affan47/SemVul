webauth_keyring_write(struct webauth_context *ctx,
                      const struct webauth_keyring *ring, const char *path)
{
    apr_file_t *file = NULL;
    size_t length;
    char *temp, *buf;
    apr_status_t code;
    apr_int32_t flags;
    int s;


    temp = apr_psprintf(ctx->pool, "%s.XXXXXX", path);
    flags = (APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_EXCL
             | APR_FOPEN_NOCLEANUP);
    code = apr_file_mktemp(&file, temp, flags, ctx->pool);
    if (code != APR_SUCCESS) {
        s = WA_ERR_FILE_OPENWRITE;
        wai_error_set_apr(ctx, s, code, "temporary keyring %s", temp);
        goto done;
    }


    s = webauth_keyring_encode(ctx, ring, &buf, &length);
    if (s != WA_ERR_NONE)
        goto done;
    code = apr_file_write_full(file, buf, length, NULL);
    if (code == APR_SUCCESS) {
        code = apr_file_close(file);
        file = NULL;
    }
    if (code != APR_SUCCESS) {
        s = WA_ERR_FILE_WRITE;
        wai_error_set_apr(ctx, s, code, "temporary keyring %s", temp);
        goto done;
    }


    code = apr_file_rename(temp, path, ctx->pool);
    if (code != APR_SUCCESS) {
        s = WA_ERR_FILE_WRITE;
        wai_error_set_apr(ctx, s, code, "renaming %s to %s", temp, path);
        goto done;
    }
    s = WA_ERR_NONE;

done:
    if (file != NULL) {
        apr_file_close(file);
        apr_file_remove(temp, ctx->pool);
    }
    return s;
}

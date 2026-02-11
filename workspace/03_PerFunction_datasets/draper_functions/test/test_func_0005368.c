cgi_temp_dir_set(apreq_handle_t *handle,
                                     const char *path)
{
    struct cgi_handle *req = (struct cgi_handle *)handle;
    const char **temp_dir = (req->parser == NULL)
                          ? &req->temp_dir
                          : &req->parser->temp_dir;


    if (*temp_dir == NULL && req->bytes_read == 0) {
        if (path != NULL)
            *temp_dir = apr_pstrdup(handle->pool, path);
        return APR_SUCCESS;
    }

    return APREQ_ERROR_MISMATCH;
}

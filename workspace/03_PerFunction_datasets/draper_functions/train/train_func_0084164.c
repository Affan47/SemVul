custom_body(apreq_handle_t *handle, const apr_table_t **t)
{
    struct custom_handle *req = (struct custom_handle*)handle;
    while (req->body_status == APR_INCOMPLETE)
        custom_parse_brigade(handle, READ_BYTES);
    *t = req->body;
    return req->body_status;
}

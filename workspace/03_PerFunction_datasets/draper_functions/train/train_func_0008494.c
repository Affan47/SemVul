respToString(apr_pool_t *pool, mhResponse_t *resp)
{
    char *str;
    const apr_table_entry_t *elts;
    const apr_array_header_t *arr;
    int i;


    str = apr_psprintf(pool, "HTTP/1.1 %d %s\r\n", resp->code,
                       codeToString(resp->code));


    arr = apr_table_elts(resp->hdrs);
    elts = (const apr_table_entry_t *)arr->elts;

    for (i = 0; i < arr->nelts; ++i) {
        str = apr_psprintf(pool, "%s%s: %s\r\n", str, elts[i].key, elts[i].val);
    }
    str = apr_psprintf(pool, "%s\r\n", str);


    if (resp->chunked == NO) {
        int i;
        for (i = 0 ; i < resp->body->nelts; i++) {
            struct iovec vec;

            vec = APR_ARRAY_IDX(resp->body, i, struct iovec);
            str = apr_psprintf(pool, "%s%.*s", str, (unsigned int)vec.iov_len,
                               (const char *)vec.iov_base);
        }
    } else {
        int i;
        bool emptyChunk = NO;
        for (i = 0 ; i < resp->chunks->nelts; i++) {
            struct iovec vec;

            vec = APR_ARRAY_IDX(resp->chunks, i, struct iovec);
            str = apr_psprintf(pool, "%s%" APR_UINT64_T_HEX_FMT "\r\n%.*s\r\n",
                               str, (apr_uint64_t)vec.iov_len,
                               (unsigned int)vec.iov_len, (char *)vec.iov_base);
            emptyChunk = vec.iov_len == 0 ? YES : NO;
        }
        if (!emptyChunk)
            str = apr_psprintf(pool, "%s0\r\n\r\n", str);
    }
    return str;
}

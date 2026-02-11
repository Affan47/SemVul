regen_key(apr_pool_t *p, apr_table_t *headers,
                             apr_array_header_t *varray, const char *oldkey)
{
    struct iovec *iov;
    int i, k;
    int nvec;
    const char *header;
    const char **elts;

    nvec = (varray->nelts * 2) + 1;
    iov = apr_palloc(p, sizeof(struct iovec) * nvec);
    elts = (const char **) varray->elts;


    for(i=0, k=0; i < varray->nelts; i++) {
        header = apr_table_get(headers, elts[i]);
        if (!header) {
            header = "";
        }
        iov[k].iov_base = (char*) elts[i];
        iov[k].iov_len = strlen(elts[i]);
        k++;
        iov[k].iov_base = (char*) header;
        iov[k].iov_len = strlen(header);
        k++;
    }
    iov[k].iov_base = (char*) oldkey;
    iov[k].iov_len = strlen(oldkey);
    k++;

    return apr_pstrcatv(p, iov, k, NULL);
}

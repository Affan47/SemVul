proc_write_ipc(fcgid_ipc *ipc_handle,
                            apr_bucket_brigade *output_brigade)
{
    apr_status_t rv;
    struct iovec vec[FCGID_VEC_COUNT];
    int nvec = 0;
    apr_bucket *e;

    for (e = APR_BRIGADE_FIRST(output_brigade);
         e != APR_BRIGADE_SENTINEL(output_brigade);
         e = APR_BUCKET_NEXT(e)) {
        apr_size_t len;
        const char* base;

        if (APR_BUCKET_IS_METADATA(e)) {
            continue;
        }

        if ((rv = apr_bucket_read(e, &base, &len,
                                  APR_BLOCK_READ)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, ipc_handle->request,
                          "mod_fcgid: can't read request from bucket");
            return rv;
        }

        vec[nvec].iov_len = len;
        vec[nvec].iov_base = (char*) base;
        if (nvec == (FCGID_VEC_COUNT - 1)) {

            if ((rv =
                 writev_it_all(ipc_handle, vec,
                               FCGID_VEC_COUNT)) != APR_SUCCESS)
                return rv;
            nvec = 0;
        }
        else
            nvec++;
    }


    if (nvec != 0) {
        if ((rv = writev_it_all(ipc_handle, vec, nvec)) != APR_SUCCESS)
            return rv;
    }

    return APR_SUCCESS;
}

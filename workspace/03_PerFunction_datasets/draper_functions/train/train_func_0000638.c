rpcsvc_callback_build_record (rpcsvc_t *rpc, int prognum, int progver,
                              int procnum, size_t payload, uint64_t xid,
                              struct iovec *recbuf)
{
        struct rpc_msg           request     = {0, };
        struct iobuf            *request_iob = NULL;
        char                    *record      = NULL;
        struct iovec             recordhdr   = {0, };
        size_t                   pagesize    = 0;
        int                      ret         = -1;

        if ((!rpc) || (!recbuf)) {
                goto out;
        }


        request_iob = iobuf_get (rpc->ctx->iobuf_pool);
        if (!request_iob) {
                goto out;
        }

        pagesize = iobuf_pagesize (request_iob);

        record = iobuf_ptr (request_iob);


        ret = rpcsvc_fill_callback (prognum, progver, procnum, payload, xid,
                                    &request);
        if (ret == -1) {
                gf_log ("rpcsvc", GF_LOG_WARNING, "cannot build a rpc-request "
                        "xid (%"PRIu64")", xid);
                goto out;
        }

        recordhdr = rpcsvc_callback_build_header (record, pagesize, &request,
                                                  payload);

        if (!recordhdr.iov_base) {
                gf_log ("rpc-clnt", GF_LOG_ERROR, "Failed to build record "
                        " header");
                iobuf_unref (request_iob);
                request_iob = NULL;
                recbuf->iov_base = NULL;
                goto out;
        }

        recbuf->iov_base = recordhdr.iov_base;
        recbuf->iov_len = recordhdr.iov_len;

out:
        return request_iob;
}

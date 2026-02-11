rpcsvc_record_build_record (rpcsvc_request_t *req, size_t payload,
                            size_t hdrlen, struct iovec *recbuf)
{
        struct rpc_msg          reply;
        struct iobuf            *replyiob = NULL;
        char                    *record = NULL;
        struct iovec            recordhdr = {0, };
        size_t                  pagesize = 0;
        size_t                  xdr_size = 0;
        rpcsvc_t                *svc = NULL;
        int                     ret = -1;

        if ((!req) || (!req->trans) || (!req->svc) || (!recbuf))
                return NULL;

        svc = req->svc;


        ret = rpcsvc_fill_reply (req, &reply);
        if (ret)
                goto err_exit;

        xdr_size = xdr_sizeof ((xdrproc_t)xdr_replymsg, &reply);


        replyiob = iobuf_get2 (svc->ctx->iobuf_pool, (xdr_size + hdrlen));
        if (!replyiob) {
                goto err_exit;
        }

        pagesize = iobuf_pagesize (replyiob);

        record = iobuf_ptr (replyiob);

        recordhdr = rpcsvc_record_build_header (record, pagesize, reply,
                                                payload);
        if (!recordhdr.iov_base) {
                gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to build record "
                        " header");
                iobuf_unref (replyiob);
                replyiob = NULL;
                recbuf->iov_base = NULL;
                goto err_exit;
        }

        recbuf->iov_base = recordhdr.iov_base;
        recbuf->iov_len = recordhdr.iov_len;
err_exit:
        return replyiob;
}

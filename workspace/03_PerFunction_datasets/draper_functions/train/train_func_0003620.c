rpc_clnt_handle_reply (struct rpc_clnt *clnt, rpc_transport_pollin_t *pollin)
{
        rpc_clnt_connection_t *conn         = NULL;
        struct saved_frame    *saved_frame  = NULL;
        int                    ret          = -1;
        struct rpc_req        *req          = NULL;
        uint32_t               xid          = 0;

        clnt = rpc_clnt_ref (clnt);
        conn = &clnt->conn;

        xid = ntoh32 (*((uint32_t *)pollin->vector[0].iov_base));
        saved_frame = lookup_frame (conn, xid);
        if (saved_frame == NULL) {
                gf_log (conn->trans->name, GF_LOG_ERROR,
                        "cannot lookup the saved frame for reply with xid (%u)",
                        xid);
                goto out;
        }

        req = saved_frame->rpcreq;
        if (req == NULL) {
                gf_log (conn->trans->name, GF_LOG_ERROR,
                        "no request with frame for xid (%u)", xid);
                goto out;
        }

        ret = rpc_clnt_reply_init (conn, pollin, req, saved_frame);
        if (ret != 0) {
                req->rpc_status = -1;
                gf_log (conn->trans->name, GF_LOG_WARNING,
                        "initialising rpc reply failed");
        }

        req->cbkfn (req, req->rsp, req->rspcnt, saved_frame->frame);

        if (req) {
                rpc_clnt_reply_deinit (req, conn->rpc_clnt->reqpool);
        }
out:

        if (saved_frame) {
                mem_put (saved_frame);
        }

        clnt = rpc_clnt_unref (clnt);
        return ret;
}

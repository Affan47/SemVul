client3_1_readv_cbk (struct rpc_req *req, struct iovec *iov, int count,
                     void *myframe)
{
        call_frame_t   *frame  = NULL;
        struct iobref  *iobref = NULL;
        struct iovec    vector[MAX_IOVEC] = {{0}, };
        struct iatt     stat   = {0,};
        gfs3_read_rsp   rsp    = {0,};
        int             ret    = 0, rspcount = 0;
        clnt_local_t   *local  = NULL;
        xlator_t         *this       = NULL;

        this = THIS;

        memset (vector, 0, sizeof (vector));

        frame = myframe;
        local = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                rsp.op_ret   = -1;
                rsp.op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_gfs3_read_rsp);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR, "XDR decoding failed");
                rsp.op_ret   = -1;
                rsp.op_errno = EINVAL;
                goto out;
        }

        if (rsp.op_ret != -1) {
                iobref = req->rsp_iobref;
                gf_stat_to_iatt (&rsp.stat, &stat);

                vector[0].iov_len = rsp.op_ret;
                if (rsp.op_ret > 0)
                        vector[0].iov_base = req->rsp[1].iov_base;
                rspcount = 1;
        }
out:
        if (rsp.op_ret == -1) {
                gf_log (this->name, GF_LOG_WARNING,
                        "remote operation failed: %s",
                        strerror (gf_error_to_errno (rsp.op_errno)));
        }
        STACK_UNWIND_STRICT (readv, frame, rsp.op_ret,
                             gf_error_to_errno (rsp.op_errno), vector, rspcount,
                             &stat, iobref);

        client_local_wipe (local);

        return 0;
}

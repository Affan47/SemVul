client3_3_writev_cbk (struct rpc_req *req, struct iovec *iov, int count,
                      void *myframe)
{
        gfs3_write_rsp rsp = {0,};
        call_frame_t   *frame = NULL;
        struct iatt  prestat  = {0,};
        struct iatt  poststat = {0,};
        int ret = 0;
        xlator_t *this       = NULL;
        dict_t  *xdata       = NULL;
        clnt_local_t    *local = NULL;


        this = THIS;

        frame = myframe;
        local = frame->local;

        if (-1 == req->rpc_status) {
                rsp.op_ret   = -1;
                rsp.op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_gfs3_truncate_rsp);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR, "XDR decoding failed");
                rsp.op_ret   = -1;
                rsp.op_errno = EINVAL;
                goto out;
        }

        if (-1 != rsp.op_ret) {
                gf_stat_to_iatt (&rsp.prestat, &prestat);
                gf_stat_to_iatt (&rsp.poststat, &poststat);
        }

        GF_PROTOCOL_DICT_UNSERIALIZE (this, xdata, (rsp.xdata.xdata_val),
                                      (rsp.xdata.xdata_len), ret,
                                      rsp.op_errno, out);

out:
        if (rsp.op_ret == -1) {
                gf_log (this->name, GF_LOG_WARNING, "remote operation failed: %s",
                        strerror (gf_error_to_errno (rsp.op_errno)));
        } else if (rsp.op_ret >= 0) {
                if (local->attempt_reopen)
                        client_attempt_reopen (local->fd, this);
        }
        CLIENT_STACK_UNWIND (writev, frame, rsp.op_ret,
                             gf_error_to_errno (rsp.op_errno), &prestat,
                             &poststat, xdata);

        free (rsp.xdata.xdata_val);

        if (xdata)
                dict_unref (xdata);

        return 0;
}

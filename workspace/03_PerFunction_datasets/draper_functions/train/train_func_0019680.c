client3_3_unlink_cbk (struct rpc_req *req, struct iovec *iov, int count,
                      void *myframe)
{
        call_frame_t    *frame      = NULL;
        gfs3_unlink_rsp  rsp        = {0,};
        struct iatt      preparent  = {0,};
        struct iatt      postparent = {0,};
        int              ret        = 0;
        xlator_t *this       = NULL;
        dict_t  *xdata       = NULL;


        this = THIS;

        frame = myframe;

        if (-1 == req->rpc_status) {
                rsp.op_ret   = -1;
                rsp.op_errno = ENOTCONN;
                goto out;
        }
        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_gfs3_unlink_rsp);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR, "XDR decoding failed");
                rsp.op_ret   = -1;
                rsp.op_errno = EINVAL;
                goto out;
        }

        if (-1 != rsp.op_ret) {
                gf_stat_to_iatt (&rsp.preparent, &preparent);
                gf_stat_to_iatt (&rsp.postparent, &postparent);
        }

        GF_PROTOCOL_DICT_UNSERIALIZE (this, xdata, (rsp.xdata.xdata_val),
                                      (rsp.xdata.xdata_len), ret,
                                      rsp.op_errno, out);

out:
        if (rsp.op_ret == -1) {
                gf_log (this->name,
                        ((gf_error_to_errno (rsp.op_errno) == ENOENT)
                        ? GF_LOG_DEBUG : GF_LOG_WARNING),
                        "remote operation failed: %s",
                        strerror (gf_error_to_errno (rsp.op_errno)));
        }

        CLIENT_STACK_UNWIND (unlink, frame, rsp.op_ret,
                             gf_error_to_errno (rsp.op_errno), &preparent,
                             &postparent, xdata);

        free (rsp.xdata.xdata_val);

        if (xdata)
                dict_unref (xdata);

        return 0;
}

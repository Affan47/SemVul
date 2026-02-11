client3_1_rchecksum (call_frame_t *frame, xlator_t *this,
                     void *data)
{
        clnt_args_t        *args     = NULL;
        int64_t             remote_fd = -1;
        clnt_conf_t        *conf     = NULL;
        gfs3_rchecksum_req  req      = {0,};
        int                 op_errno = ESTALE;
        int                 ret        = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;
        conf = this->private;

        CLIENT_GET_REMOTE_FD(conf, args->fd, remote_fd, op_errno, unwind);

        req.len    = args->len;
        req.offset = args->offset;
        req.fd     = remote_fd;

        GF_PROTOCOL_DICT_SERIALIZE (this, args->xdata, (&req.xdata.xdata_val),
                                    req.xdata.xdata_len, op_errno, unwind);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_RCHECKSUM,
                                     client3_1_rchecksum_cbk, NULL,
                                     NULL, 0, NULL,
                                     0, NULL,
                                     (xdrproc_t)xdr_gfs3_rchecksum_req);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "failed to send the fop");
        }

        if (req.xdata.xdata_val)
                GF_FREE (req.xdata.xdata_val);

        return 0;
unwind:
        CLIENT_STACK_UNWIND (rchecksum, frame, -1, op_errno, 0, NULL, NULL);
        if (req.xdata.xdata_val)
                GF_FREE (req.xdata.xdata_val);

        return 0;
}

client3_3_ftruncate (call_frame_t *frame, xlator_t *this,
                     void *data)
{
        clnt_args_t        *args     = NULL;
        int64_t             remote_fd = -1;
        clnt_conf_t        *conf     = NULL;
        gfs3_ftruncate_req  req      = {{0,},};
        int                 op_errno = EINVAL;
        int                 ret      = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;

        conf = this->private;

        CLIENT_GET_REMOTE_FD (this, args->fd, DEFAULT_REMOTE_FD,
                              remote_fd, op_errno, unwind);

        req.offset = args->offset;
        req.fd     = remote_fd;
        memcpy (req.gfid, args->fd->inode->gfid, 16);

        GF_PROTOCOL_DICT_SERIALIZE (this, args->xdata, (&req.xdata.xdata_val),
                                    req.xdata.xdata_len, op_errno, unwind);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_FTRUNCATE,
                                     client3_3_ftruncate_cbk, NULL,
                                     NULL, 0, NULL, 0,
                                     NULL, (xdrproc_t)xdr_gfs3_ftruncate_req);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "failed to send the fop");
        }

        GF_FREE (req.xdata.xdata_val);

        return 0;
unwind:
        CLIENT_STACK_UNWIND (ftruncate, frame, -1, op_errno, NULL, NULL, NULL);
        GF_FREE (req.xdata.xdata_val);

        return 0;
}

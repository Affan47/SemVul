client3_1_fstat (call_frame_t *frame, xlator_t *this,
                 void *data)
{
        clnt_args_t    *args     = NULL;
        gfs3_fstat_req  req      = {{0,},};
        int64_t         remote_fd = -1;
        clnt_conf_t    *conf     = NULL;
        int             op_errno = ESTALE;
        int           ret        = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;
        conf = this->private;

        CLIENT_GET_REMOTE_FD(conf, args->fd, remote_fd, unwind);

        req.fd = remote_fd;
        memcpy (req.gfid, args->fd->inode->gfid, 16);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_FSTAT, client3_1_fstat_cbk, NULL,
                                     NULL, 0, NULL, 0,
                                     NULL, (xdrproc_t)xdr_gfs3_fstat_req);
        if (ret) {
                op_errno = ENOTCONN;
                goto unwind;
        }
        return 0;
unwind:
        gf_log (this->name, GF_LOG_WARNING, "failed to send the fop: %s", strerror (op_errno));
        STACK_UNWIND_STRICT (fstat, frame, -1, op_errno, NULL);
        return 0;
}

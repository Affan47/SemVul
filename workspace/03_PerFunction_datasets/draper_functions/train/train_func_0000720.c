client3_1_finodelk (call_frame_t *frame, xlator_t *this,
                    void *data)
{
        clnt_args_t       *args     = NULL;
        gfs3_finodelk_req  req      = {{0,},};
        int32_t            gf_cmd   = 0;
        int32_t            gf_type  = 0;
        int64_t            remote_fd = -1;
        clnt_conf_t       *conf     = NULL;
        int                op_errno = ESTALE;
        int           ret        = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;
        conf = this->private;

        CLIENT_GET_REMOTE_FD(conf, args->fd, remote_fd, op_errno, unwind);

        if (args->cmd == F_GETLK || args->cmd == F_GETLK64)
                gf_cmd = GF_LK_GETLK;
        else if (args->cmd == F_SETLK || args->cmd == F_SETLK64)
                gf_cmd = GF_LK_SETLK;
        else if (args->cmd == F_SETLKW || args->cmd == F_SETLKW64)
                gf_cmd = GF_LK_SETLKW;
        else {
                gf_log (this->name, GF_LOG_WARNING,
                        "Unknown cmd (%d)!", gf_cmd);
                goto unwind;
        }

        switch (args->flock->l_type) {
        case F_RDLCK:
                gf_type = GF_LK_F_RDLCK;
                break;
        case F_WRLCK:
                gf_type = GF_LK_F_WRLCK;
                break;
        case F_UNLCK:
                gf_type = GF_LK_F_UNLCK;
                break;
        }

        req.volume = (char *)args->volume;
        req.fd    = remote_fd;
        req.cmd   = gf_cmd;
        req.type  = gf_type;
        gf_proto_flock_from_flock (&req.flock, args->flock);
        memcpy (req.gfid, args->fd->inode->gfid, 16);

        GF_PROTOCOL_DICT_SERIALIZE (this, args->xdata, (&req.xdata.xdata_val),
                                    req.xdata.xdata_len, op_errno, unwind);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_FINODELK,
                                     client3_1_finodelk_cbk, NULL,
                                     NULL, 0, NULL, 0,
                                     NULL, (xdrproc_t)xdr_gfs3_finodelk_req);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "failed to send the fop");
        }

        if (req.xdata.xdata_val)
                GF_FREE (req.xdata.xdata_val);
        return 0;
unwind:
        CLIENT_STACK_UNWIND (finodelk, frame, -1, op_errno, NULL);
        if (req.xdata.xdata_val)
                GF_FREE (req.xdata.xdata_val);

        return 0;
}

client3_3_opendir (call_frame_t *frame, xlator_t *this,
                   void *data)
{
        clnt_local_t     *local    = NULL;
        clnt_conf_t      *conf     = NULL;
        clnt_args_t      *args     = NULL;
        gfs3_opendir_req  req      = {{0,},};
        int               ret      = 0;
        int               op_errno = ESTALE;

        if (!frame || !this || !data)
                goto unwind;

        args = data;

        local = mem_get0 (this->local_pool);
        if (!local) {
                op_errno = ENOMEM;
                goto unwind;
        }
        if (!(args->loc && args->loc->inode))
                goto unwind;

        local->fd = fd_ref (args->fd);
        loc_copy (&local->loc, args->loc);
        frame->local = local;

        if (!uuid_is_null (args->loc->inode->gfid))
                memcpy (req.gfid,  args->loc->inode->gfid, 16);
        else
                memcpy (req.gfid, args->loc->gfid, 16);

        GF_ASSERT_AND_GOTO_WITH_ERROR (this->name,
                                       !uuid_is_null (*((uuid_t*)req.gfid)),
                                       unwind, op_errno, EINVAL);

        conf = this->private;

        GF_PROTOCOL_DICT_SERIALIZE (this, args->xdata, (&req.xdata.xdata_val),
                                    req.xdata.xdata_len, op_errno, unwind);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_OPENDIR, client3_3_opendir_cbk,
                                     NULL, NULL, 0, NULL, 0, NULL,
                                     (xdrproc_t)xdr_gfs3_opendir_req);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "failed to send the fop");
        }

        GF_FREE (req.xdata.xdata_val);

        return 0;

unwind:
        CLIENT_STACK_UNWIND (opendir, frame, -1, op_errno, NULL, NULL);

        GF_FREE (req.xdata.xdata_val);

        return 0;
}

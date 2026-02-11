client3_1_stat (call_frame_t *frame, xlator_t *this,
                void *data)
{
        clnt_conf_t   *conf     = NULL;
        clnt_args_t   *args     = NULL;
        gfs3_stat_req  req      = {{0,},};
        int            ret      = 0;
        int            op_errno = ESTALE;

        if (!frame || !this || !data)
                goto unwind;

        args = data;
        if (!(args->loc && args->loc->inode))
                goto unwind;

        if (!uuid_is_null (args->loc->inode->gfid))
                memcpy (req.gfid,  args->loc->inode->gfid, 16);
        else
                memcpy (req.gfid, args->loc->gfid, 16);

        GF_ASSERT_AND_GOTO_WITH_ERROR (this->name,
                                       !uuid_is_null (*((uuid_t*)req.gfid)),
                                       unwind, op_errno, EINVAL);
        req.path = (char *)args->loc->path;
        conf = this->private;

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_STAT, client3_1_stat_cbk, NULL,
                                     NULL, 0, NULL, 0, NULL,
                                     (xdrproc_t)xdr_gfs3_stat_req);
        if (ret) {
                op_errno = ENOTCONN;
                goto unwind;
        }

        return 0;
unwind:
        gf_log (this->name, GF_LOG_WARNING, "failed to send the fop %s",
                strerror (op_errno));
        STACK_UNWIND_STRICT (stat, frame, -1, op_errno, NULL);
        return 0;
}

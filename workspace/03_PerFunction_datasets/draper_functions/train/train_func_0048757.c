client3_3_unlink (call_frame_t *frame, xlator_t *this,
                  void *data)
{
        clnt_conf_t     *conf     = NULL;
        clnt_args_t     *args     = NULL;
        gfs3_unlink_req  req      = {{0,},};
        int              ret      = 0;
        int              op_errno = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;

        if (!(args->loc && args->loc->parent))
                goto unwind;

        if (!uuid_is_null (args->loc->parent->gfid))
                memcpy (req.pargfid,  args->loc->parent->gfid, 16);
        else
                memcpy (req.pargfid, args->loc->pargfid, 16);

        GF_ASSERT_AND_GOTO_WITH_ERROR (this->name,
                                       !uuid_is_null (*((uuid_t*)req.pargfid)),
                                       unwind, op_errno, EINVAL);
        req.bname = (char *)args->loc->name;
        conf = this->private;

        GF_PROTOCOL_DICT_SERIALIZE (this, args->xdata, (&req.xdata.xdata_val),
                                    req.xdata.xdata_len, op_errno, unwind);

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_UNLINK,
                                     client3_3_unlink_cbk, NULL,
                                     NULL, 0, NULL, 0,
                                     NULL, (xdrproc_t)xdr_gfs3_unlink_req);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "failed to send the fop");
        }

        GF_FREE (req.xdata.xdata_val);

        return 0;
unwind:
        CLIENT_STACK_UNWIND (unlink, frame, -1, op_errno, NULL, NULL, NULL);
        GF_FREE (req.xdata.xdata_val);

        return 0;
}

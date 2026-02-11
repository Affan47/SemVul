server_rmdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *preparent,
                  struct iatt *postparent, dict_t *xdata)
{
        gfs3_rmdir_rsp    rsp    = {0,};
        server_state_t   *state  = NULL;
        inode_t          *parent = NULL;
        rpcsvc_request_t *req    = NULL;

        req = frame->local;
        state = CALL_STATE(frame);

        GF_PROTOCOL_DICT_SERIALIZE (this, xdata, (&rsp.xdata.xdata_val),
                                    rsp.xdata.xdata_len, op_errno, out);

        if (op_ret) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": RMDIR %s (%s/%s) ==> (%s)",
                        frame->root->unique, state->loc.path,
                        uuid_utoa (state->resolve.pargfid),
                        state->resolve.bname, strerror (op_errno));
                goto out;
        }

        inode_unlink (state->loc.inode, state->loc.parent,
                      state->loc.name);
        parent = inode_parent (state->loc.inode, 0, NULL);
        if (parent)


                inode_unref (parent);
        else
                inode_forget (state->loc.inode, 0);

        gf_stat_from_iatt (&rsp.preparent, preparent);
        gf_stat_from_iatt (&rsp.postparent, postparent);

out:
        rsp.op_ret    = op_ret;
        rsp.op_errno  = gf_errno_to_error (op_errno);

        server_submit_reply (frame, req, &rsp, NULL, 0, NULL,
                             (xdrproc_t)xdr_gfs3_rmdir_rsp);

        GF_FREE (rsp.xdata.xdata_val);

        return 0;
}

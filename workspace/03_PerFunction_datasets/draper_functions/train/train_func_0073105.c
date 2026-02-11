server_fxattrop_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, dict_t *dict,
                     dict_t *xdata)
{
        gfs3_xattrop_rsp  rsp   = {0,};
        server_state_t   *state = NULL;
        rpcsvc_request_t *req   = NULL;

        state = CALL_STATE(frame);

        if (op_ret < 0) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "%"PRId64": FXATTROP %"PRId64" (%s) ==> %"PRId32" (%s)",
                        frame->root->unique, state->resolve.fd_no,
                        state->fd ? uuid_utoa (state->fd->inode->gfid) : "--",
                        op_ret, strerror (op_errno));
                goto out;
        }

        if ((op_ret >= 0) && dict) {
                GF_PROTOCOL_DICT_SERIALIZE (this, dict,
                                            (&rsp.dict.dict_val),
                                            rsp.dict.dict_len,
                                            op_errno, out);
        }

        GF_PROTOCOL_DICT_SERIALIZE (this, xdata, (&rsp.xdata.xdata_val),
                                    rsp.xdata.xdata_len, op_errno, out);


out:
        req               = frame->local;

        rsp.op_ret        = op_ret;
        rsp.op_errno      = gf_errno_to_error (op_errno);

        if (op_ret == -1)
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": FXATTROP %"PRId64" (%s) ==> %"PRId32" (%s)",
                        frame->root->unique, state->resolve.fd_no,
                        state->fd ? uuid_utoa (state->fd->inode->gfid) : "--",
                        op_ret, strerror (op_errno));

        server_submit_reply (frame, req, &rsp, NULL, 0, NULL,
                             (xdrproc_t)xdr_gfs3_fxattrop_rsp);

        if (rsp.dict.dict_val)
                GF_FREE (rsp.dict.dict_val);

        if (rsp.xdata.xdata_val)
                GF_FREE (rsp.xdata.xdata_val);

        return 0;
}

server_inodelk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, dict_t *xdata)
{
        gf_common_rsp        rsp   = {0,};
        server_connection_t *conn  = NULL;
        server_state_t      *state = NULL;
        rpcsvc_request_t    *req   = NULL;

        req           = frame->local;

        GF_PROTOCOL_DICT_SERIALIZE (this, xdata, (&rsp.xdata.xdata_val),
                                    rsp.xdata.xdata_len, op_errno, out);

        conn  = SERVER_CONNECTION(frame);
        state = CALL_STATE(frame);

        if (op_ret >= 0) {
                if (state->flock.l_type == F_UNLCK)
                        gf_del_locker (conn, state->volume,
                                       &state->loc, NULL, &frame->root->lk_owner,
                                       GF_FOP_INODELK);
                else
                        gf_add_locker (conn, state->volume,
                                       &state->loc, NULL, frame->root->pid,
                                       &frame->root->lk_owner,
                                       GF_FOP_INODELK);
        } else if ((op_errno != ENOSYS) && (op_errno != EAGAIN)) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": INODELK %s (%s) ==> %"PRId32" (%s)",
                        frame->root->unique, state->loc.path,
                        state->loc.inode ? uuid_utoa (state->loc.inode->gfid) :
                        "--", op_ret, strerror (op_errno));
        }

out:
        rsp.op_ret    = op_ret;
        rsp.op_errno  = gf_errno_to_error (op_errno);

        server_submit_reply (frame, req, &rsp, NULL, 0, NULL,
                             (xdrproc_t)xdr_gf_common_rsp);

        if (rsp.xdata.xdata_val)
                GF_FREE (rsp.xdata.xdata_val);

        return 0;
}

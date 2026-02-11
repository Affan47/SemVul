server_fentrylk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno)
{
        gf_common_rsp        rsp   = {0,};
        server_connection_t *conn  = NULL;
        server_state_t      *state = NULL;
        rpcsvc_request_t    *req   = NULL;

        req           = frame->local;

        rsp.op_ret    = op_ret;
        rsp.op_errno  = gf_errno_to_error (op_errno);

        conn  = SERVER_CONNECTION(frame);
        state = CALL_STATE(frame);
        if (op_ret >= 0) {
                if (state->cmd == ENTRYLK_UNLOCK)
                        gf_del_locker (conn->ltable, state->volume,
                                       NULL, state->fd, frame->root->lk_owner, GF_FOP_ENTRYLK);
                else
                        gf_add_locker (conn->ltable, state->volume,
                                       NULL, state->fd, frame->root->pid,
                                       frame->root->lk_owner, GF_FOP_ENTRYLK);
        } else if ((op_errno != ENOSYS) && (op_errno != EAGAIN)) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": FENTRYLK %"PRId64" (%s) "
                        " ==> %"PRId32" (%s)",
                        frame->root->unique, state->resolve.fd_no,
                        state->fd ? uuid_utoa (state->fd->inode->gfid) : "--",
                        op_ret, strerror (op_errno));
        }

        server_submit_reply (frame, req, &rsp, NULL, 0, NULL,
                             (xdrproc_t)xdr_gf_common_rsp);

        return 0;
}

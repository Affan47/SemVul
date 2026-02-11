server_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno,
                  struct iovec *vector, int32_t count,
                  struct iatt *stbuf, struct iobref *iobref)
{
        gfs3_read_rsp     rsp   = {0,};
        server_state_t   *state = NULL;
        rpcsvc_request_t *req   = NULL;

        req           = frame->local;

        rsp.op_ret    = op_ret;
        rsp.op_errno  = gf_errno_to_error (op_errno);

        state = CALL_STATE(frame);
        if (op_ret >= 0) {
                gf_stat_from_iatt (&rsp.stat, stbuf);
                rsp.size = op_ret;
        } else {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": READV %"PRId64" (%s) ==> %"PRId32" (%s)",
                        frame->root->unique, state->resolve.fd_no,
                        state->fd ? uuid_utoa (state->fd->inode->gfid) : "--",
                        op_ret, strerror (op_errno));
        }

        server_submit_reply (frame, req, &rsp, vector, count, iobref,
                             (xdrproc_t)xdr_gfs3_read_rsp);

        return 0;
}

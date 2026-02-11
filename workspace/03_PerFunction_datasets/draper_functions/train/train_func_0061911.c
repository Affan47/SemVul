trace_opendir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, fd_t *fd)
{
        if (trace_fop_names[GF_FOP_OPENDIR].enabled) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": gfid=%s op_ret=%d, op_errno=%d, fd=%p",
                        frame->root->unique, uuid_utoa (frame->local),
                        op_ret, op_errno, fd);
        }


        if (op_ret >= 0)
                fd_ctx_set (fd, this, 0);

        frame->local = NULL;
        STACK_UNWIND_STRICT (opendir, frame, op_ret, op_errno, fd);
        return 0;
}

quiesce_fsyncdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, dict_t *xdata)
{
        call_stub_t    *stub = NULL;
        quiesce_local_t *local = NULL;

        local = frame->local;
        frame->local = NULL;
        if ((op_ret == -1) && (op_errno == ENOTCONN)) {

                stub = fop_fsyncdir_stub (frame, default_fsyncdir_resume,
                                          local->fd, local->flag, xdata);
                if (!stub) {
                        STACK_UNWIND_STRICT (fsyncdir, frame, -1, ENOMEM, NULL);
                        goto out;
                }

                gf_quiesce_enqueue (this, stub);
                goto out;
        }

        STACK_UNWIND_STRICT (fsyncdir, frame, op_ret, op_errno, xdata);
out:
        gf_quiesce_local_wipe (this, local);

        return 0;
}

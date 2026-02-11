quiesce_fstat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *buf, dict_t *xdata)
{
        call_stub_t    *stub = NULL;
        quiesce_local_t *local = NULL;

        local = frame->local;
        frame->local = NULL;
        if ((op_ret == -1) && (op_errno == ENOTCONN)) {

                stub = fop_fstat_stub (frame, default_fstat_resume,
                                       local->fd, xdata);
                if (!stub) {
                        STACK_UNWIND_STRICT (fstat, frame, -1, ENOMEM,
                                             NULL, NULL);
                        goto out;
                }

                gf_quiesce_enqueue (this, stub);
                goto out;
        }

        STACK_UNWIND_STRICT (fstat, frame, op_ret, op_errno, buf, xdata);
out:
        gf_quiesce_local_wipe (this, local);

        return 0;
}

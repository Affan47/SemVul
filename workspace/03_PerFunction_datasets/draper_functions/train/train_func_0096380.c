mdc_truncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno,
                  struct iatt *prebuf, struct iatt *postbuf, dict_t *xdata)
{
        mdc_local_t  *local = NULL;

        local = frame->local;

        if (op_ret != 0)
                goto out;

        if (!local)
                goto out;

        mdc_inode_iatt_set (this, local->loc.inode, postbuf);

out:
        MDC_STACK_UNWIND (truncate, frame, op_ret, op_errno, prebuf, postbuf,
                          xdata);

        return 0;
}

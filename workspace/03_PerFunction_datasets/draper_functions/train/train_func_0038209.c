ra_flush_cbk (call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
              int32_t op_errno, dict_t *xdata)
{
        GF_ASSERT (frame);
        STACK_UNWIND_STRICT (flush, frame, op_ret, op_errno, xdata);
        return 0;
}

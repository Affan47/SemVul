io_stats_readlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, const char *buf,
                       struct iatt *sbuf)
{
        UPDATE_PROFILE_STATS (frame, READLINK);
        STACK_UNWIND_STRICT (readlink, frame, op_ret, op_errno, buf, sbuf);
        return 0;
}

io_stats_rename_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, struct iatt *buf,
                     struct iatt *preoldparent, struct iatt *postoldparent,
                     struct iatt *prenewparent, struct iatt *postnewparent, dict_t *xdata)
{
        UPDATE_PROFILE_STATS (frame, RENAME);
        STACK_UNWIND_STRICT (rename, frame, op_ret, op_errno, buf,
                             preoldparent, postoldparent,
                             prenewparent, postnewparent, xdata);
        return 0;
}

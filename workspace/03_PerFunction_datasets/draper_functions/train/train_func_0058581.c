io_stats_opendir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, fd_t *fd, dict_t *xdata)
{
        struct ios_stat *iosstat = NULL;
        int              ret     = -1;

        UPDATE_PROFILE_STATS (frame, OPENDIR);
        if (op_ret < 0)
                goto unwind;

        ios_fd_ctx_set (fd, this, 0);

        ret = ios_inode_ctx_get (fd->inode, this, &iosstat);
        if (!ret)
                BUMP_STATS (iosstat, IOS_STATS_TYPE_OPENDIR);

unwind:
        STACK_UNWIND_STRICT (opendir, frame, op_ret, op_errno, fd, xdata);
        return 0;
}

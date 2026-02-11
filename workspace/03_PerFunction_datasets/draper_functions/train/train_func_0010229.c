io_stats_readdirp (call_frame_t *frame, xlator_t *this, fd_t *fd, size_t size,
                   off_t offset, dict_t *dict)
{
        frame->local = fd->inode;
        START_FOP_LATENCY (frame);

        STACK_WIND (frame, io_stats_readdirp_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readdirp,
                    fd, size, offset, dict);
        return 0;
}

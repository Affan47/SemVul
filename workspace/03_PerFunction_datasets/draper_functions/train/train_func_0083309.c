trash_ftruncate_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                           int32_t op_ret, int32_t op_errno,
                           struct iovec *vector, int32_t count,
                           struct iatt *stbuf, struct iobref *iobuf)
{
        trash_local_t *local = NULL;

        local = frame->local;
        local->fsize = stbuf->ia_size;

        if (op_ret == -1) {
                STACK_WIND (frame, trash_ftruncate_unlink_cbk,
                            FIRST_CHILD(this), FIRST_CHILD(this)->fops->unlink,
                            &local->newloc);
                return 0;
        }

        STACK_WIND (frame, trash_ftruncate_writev_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->writev,
                    local->newfd, vector, count, local->cur_offset, NULL);

        return 0;
}

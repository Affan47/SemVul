mq_dirty_inode_readdir (call_frame_t *frame,
                        void *cookie,
                        xlator_t *this,
                        int32_t op_ret,
                        int32_t op_errno,
                        fd_t *fd, dict_t *xdata)
{
        quota_local_t *local = NULL;

        local = frame->local;

        if (op_ret == -1) {
                local->err = -1;
                mq_release_lock_on_dirty_inode (frame, NULL, this, 0, 0, NULL);
                return 0;
        }

        if (local->fd == NULL)
                local->fd = fd_ref (fd);

        STACK_WIND (frame,
                    mq_readdir_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->readdir,
                    local->fd, READDIR_BUF, local->d_off, xdata);

        return 0;
}

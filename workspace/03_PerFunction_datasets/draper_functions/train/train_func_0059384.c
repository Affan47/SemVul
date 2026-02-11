mq_xattr_creation_release_lock (call_frame_t *frame, void *cookie,
                                xlator_t *this, int32_t op_ret,
                                int32_t op_errno)
{
        struct gf_flock  lock  = {0, };
        quota_local_t   *local = NULL;

        local = frame->local;

        lock.l_type   = F_UNLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start  = 0;
        lock.l_len    = 0;
        lock.l_pid    = 0;

        STACK_WIND (frame,
                    mq_inode_creation_done,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->inodelk,
                    this->name, &local->loc,
                    F_SETLKW, &lock);

        return 0;
}

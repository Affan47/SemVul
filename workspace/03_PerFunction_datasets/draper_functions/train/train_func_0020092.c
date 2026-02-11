mq_release_lock_on_dirty_inode (call_frame_t *frame, void *cookie, xlator_t *this,
                                int32_t op_ret, int32_t op_errno, dict_t *xdata)
{
        struct gf_flock   lock  = {0, };
        quota_local_t    *local = NULL;
        loc_t             loc = {0, };
	int               ret = -1;

        local = frame->local;

        if (op_ret == -1) {
                local->err = -1;

                mq_dirty_inode_updation_done (frame, NULL, this, 0, 0, NULL);

                return 0;
        }

        if (op_ret == 0)
                local->ctx->dirty = 0;

        lock.l_type   = F_UNLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start  = 0;
        lock.l_len    = 0;
        lock.l_pid    = 0;

        ret = loc_copy (&loc, &local->loc);
	if (ret == -1) {
                local->err = -1;
                frame->local = NULL;
                mq_dirty_inode_updation_done (frame, NULL, this, 0, 0, NULL);
                return 0;
        }

        if (local->loc.inode == NULL) {
                gf_log (this->name, GF_LOG_WARNING,
                        "Inode is NULL, so can't stackwind.");
                goto out;
        }

        STACK_WIND (frame,
                    mq_dirty_inode_updation_done,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->inodelk,
                    this->name, &loc, F_SETLKW, &lock, NULL);

        loc_wipe (&loc);

        return 0;
out:
        mq_dirty_inode_updation_done (frame, NULL, this, -1, 0, NULL);

        return 0;
}

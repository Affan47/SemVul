pl_send_prelock_unlock (xlator_t *this, pl_inode_t *pl_inode,
                        posix_lock_t *old_lock)
{
        struct gf_flock  flock       = {0,};
        posix_lock_t *unlock_lock = NULL;

        struct list_head granted_list;
        posix_lock_t     *tmp = NULL;
        posix_lock_t     *lock = NULL;

        int ret = -1;

        INIT_LIST_HEAD (&granted_list);

        flock.l_type   = F_UNLCK;
        flock.l_whence = old_lock->user_flock.l_whence;
        flock.l_start  = old_lock->user_flock.l_start;
        flock.l_len    = old_lock->user_flock.l_len;


        unlock_lock = new_posix_lock (&flock, old_lock->transport,
                                      old_lock->client_pid, &old_lock->owner,
                                      old_lock->fd);
        GF_VALIDATE_OR_GOTO (this->name, unlock_lock, out);
        ret = 0;

        __insert_and_merge (pl_inode, unlock_lock);

        __grant_blocked_locks (this, pl_inode, &granted_list);

        list_for_each_entry_safe (lock, tmp, &granted_list, list) {
                list_del_init (&lock->list);

                pl_trace_out (this, lock->frame, NULL, NULL, F_SETLKW,
                              &lock->user_flock, 0, 0, NULL);

                STACK_UNWIND_STRICT (lk, lock->frame, 0, 0,
                                     &lock->user_flock, NULL);

                GF_FREE (lock);
        }

out:
        return ret;
}

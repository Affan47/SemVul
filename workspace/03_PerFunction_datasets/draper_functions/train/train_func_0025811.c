pl_verify_reservelk (xlator_t *this, pl_inode_t *pl_inode,
                     posix_lock_t *lock, int can_block)
{
        int ret = 0;

        pthread_mutex_lock (&pl_inode->mutex);
        {
                if (__reservelk_conflict (this, pl_inode, lock)) {
                        gf_log (this->name, GF_LOG_TRACE,
                                "Found conflicting reservelk. Blocking until reservelk is unlocked.");
                        lock->blocked = can_block;
                        list_add_tail (&lock->list, &pl_inode->blocked_calls);
                        ret = -1;
                        goto unlock;
                }

                gf_log (this->name, GF_LOG_TRACE,
                        "no conflicting reservelk found. Call continuing");
                ret = 0;

        }
unlock:
        pthread_mutex_unlock (&pl_inode->mutex);

        return ret;

}

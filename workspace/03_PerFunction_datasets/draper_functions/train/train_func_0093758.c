first_conflicting_overlap (pl_inode_t *pl_inode, posix_lock_t *lock)
{
        posix_lock_t *l = NULL;
        posix_lock_t *conf = NULL;

        pthread_mutex_lock (&pl_inode->mutex);
        {
                list_for_each_entry (l, &pl_inode->ext_list, list) {
                        if (l->blocked)
                                continue;

                        if (locks_overlap (l, lock)) {
                                if (same_owner (l, lock))
                                        continue;

                                if ((l->fl_type == F_WRLCK) ||
                                    (lock->fl_type == F_WRLCK)) {
                                        conf = l;
                                        goto unlock;
                                }
                        }
                }
        }
unlock:
        pthread_mutex_unlock (&pl_inode->mutex);

        return conf;
}

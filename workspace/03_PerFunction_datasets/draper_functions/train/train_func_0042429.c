__get_inodelk_count (xlator_t *this, pl_inode_t *pl_inode)
{
        int32_t            count  = 0;
        pl_inode_lock_t   *lock   = NULL;
        pl_dom_list_t     *dom    = NULL;

        list_for_each_entry (dom, &pl_inode->dom_list, inode_list) {
                list_for_each_entry (lock, &dom->inodelk_list, list) {

                        gf_log (this->name, GF_LOG_DEBUG,
                                " XATTR DEBUG"
                                " domain: %s %s (pid=%d) (lk-owner=%"PRIu64") %"PRId64" - %"PRId64" "
                                "state = Active",
                                dom->domain,
                                lock->fl_type == F_UNLCK ? "Unlock" : "Lock",
                                lock->client_pid,
                                lock->owner,
                                lock->user_flock.l_start,
                                lock->user_flock.l_len);

                        count++;
                }

                list_for_each_entry (lock, &dom->blocked_inodelks, blocked_locks) {

                        gf_log (this->name, GF_LOG_DEBUG,
                                " XATTR DEBUG"
                                " domain: %s %s (pid=%d) (lk-owner=%"PRIu64") %"PRId64" - %"PRId64" "
                                "state = Blocked",
                                dom->domain,
                                lock->fl_type == F_UNLCK ? "Unlock" : "Lock",
                                lock->client_pid,
                                lock->owner,
                                lock->user_flock.l_start,
                                lock->user_flock.l_len);

                        count++;
                }

        }

        return count;
}

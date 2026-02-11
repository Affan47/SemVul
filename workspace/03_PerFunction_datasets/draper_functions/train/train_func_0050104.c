release_entry_locks_for_transport (xlator_t *this, pl_inode_t *pinode,
                                   pl_dom_list_t *dom, void *trans)
{
        pl_entry_lock_t  *lock = NULL;
        pl_entry_lock_t  *tmp = NULL;
        struct list_head  granted;
        struct list_head  released;

        INIT_LIST_HEAD (&granted);
        INIT_LIST_HEAD (&released);

        pthread_mutex_lock (&pinode->mutex);
        {
                list_for_each_entry_safe (lock, tmp, &dom->blocked_entrylks,
                                          blocked_locks) {
                        if (lock->trans != trans)
                                continue;

                        list_del_init (&lock->blocked_locks);

                        gf_log (this->name, GF_LOG_TRACE,
                                "releasing lock on  held by "
                                "{transport=%p}",trans);

                        list_add (&lock->blocked_locks, &released);

                }

                list_for_each_entry_safe (lock, tmp, &dom->entrylk_list,
                                          domain_list) {
                        if (lock->trans != trans)
                                continue;

                        list_del_init (&lock->domain_list);

                        gf_log (this->name, GF_LOG_TRACE,
                                "releasing lock on  held by "
                                "{transport=%p}",trans);

                        GF_FREE ((char *)lock->basename);
                        GF_FREE (lock);
                }

                __grant_blocked_entry_locks (this, pinode, dom, &granted);

        }

        pthread_mutex_unlock (&pinode->mutex);

        list_for_each_entry_safe (lock, tmp, &released, blocked_locks) {
                list_del_init (&lock->blocked_locks);

                STACK_UNWIND_STRICT (entrylk, lock->frame, -1, EAGAIN, NULL);

                if (lock->basename)
                        GF_FREE ((char *)lock->basename);
                GF_FREE (lock);

        }

        list_for_each_entry_safe (lock, tmp, &granted, blocked_locks) {
                list_del_init (&lock->blocked_locks);

                STACK_UNWIND_STRICT (entrylk, lock->frame, 0, 0, NULL);

                if (lock->basename)
                        GF_FREE ((char *)lock->basename);
                GF_FREE (lock);
        }

        return 0;
}

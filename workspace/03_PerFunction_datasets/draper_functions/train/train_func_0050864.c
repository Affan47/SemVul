__dump_entrylks (pl_inode_t *pl_inode)
{
        pl_dom_list_t   *dom  = NULL;
        pl_entry_lock_t *lock = NULL;
        int             count = 0;
        char            key[GF_DUMP_MAX_BUF_LEN];

        char tmp[256];

        list_for_each_entry (dom, &pl_inode->dom_list, inode_list) {

                count = 0;

                gf_proc_dump_build_key(key,
                                       "lock-dump.domain",
                                       "domain");
                gf_proc_dump_write(key, "%s", dom->domain);

                list_for_each_entry (lock, &dom->entrylk_list, domain_list) {

                        gf_proc_dump_build_key(key,
                                               "xlator.feature.locks.lock-dump.domain.entrylk",
                                               "entrylk[%d](ACTIVE)", count );
                        if (lock->blkd_time.tv_sec == 0 && lock->blkd_time.tv_usec == 0) {
                                snprintf (tmp, 256," %s on %s pid = %llu, owner=%llu, transport=%p,"
                                          " granted at %s",
                                          lock->type == ENTRYLK_RDLCK ? "ENTRYLK_RDLCK" :
                                          "ENTRYLK_WRLCK", lock->basename,
                                          (unsigned long long) lock->client_pid,
                                          (unsigned long long) lock->owner, lock->trans,
                                          ctime (&lock->granted_time.tv_sec));
                        } else {
                                snprintf (tmp, 256," %s on %s pid = %llu, owner=%llu, transport=%p,"
                                          " blocked at %s, granted at %s",
                                          lock->type == ENTRYLK_RDLCK ? "ENTRYLK_RDLCK" :
                                          "ENTRYLK_WRLCK", lock->basename,
                                          (unsigned long long) lock->client_pid,
                                          (unsigned long long) lock->owner, lock->trans,
                                          ctime (&lock->blkd_time.tv_sec),
                                          ctime (&lock->granted_time.tv_sec));
                        }

                        gf_proc_dump_write(key, tmp);

                        count++;
                }

                list_for_each_entry (lock, &dom->blocked_entrylks, blocked_locks) {

                        gf_proc_dump_build_key(key,
                                               "xlator.feature.locks.lock-dump.domain.entrylk",
                                               "entrylk[%d](BLOCKED)", count );
                        snprintf (tmp, 256," %s on %s pid = %llu, owner=%llu, transport=%p,"
                                  " blocked at %s",
                                  lock->type == ENTRYLK_RDLCK ? "ENTRYLK_RDLCK" :
                                  "ENTRYLK_WRLCK", lock->basename,
                                  (unsigned long long) lock->client_pid,
                                  (unsigned long long) lock->owner, lock->trans,
                                  ctime (&lock->blkd_time.tv_sec));

                        gf_proc_dump_write(key, tmp);

                        count++;
                }

        }

}

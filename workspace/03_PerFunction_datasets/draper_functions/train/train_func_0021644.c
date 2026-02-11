__dump_posixlks (pl_inode_t *pl_inode)
{
        posix_lock_t    *lock = NULL;
        int             count = 0;
        char            key[GF_DUMP_MAX_BUF_LEN];

        char tmp[256];

      list_for_each_entry (lock, &pl_inode->ext_list, list) {

              SET_FLOCK_PID (&lock->user_flock, lock);
              gf_proc_dump_build_key(key,
                                     "posixlk",
                                     "posixlk[%d](%s)",
                                     count,
                                     lock->blocked ? "BLOCKED" : "ACTIVE");
              pl_dump_lock (tmp, 256, &lock->user_flock,
                            lock->owner, lock->transport,
                            &lock->granted_time.tv_sec, &lock->blkd_time.tv_sec,
                            (lock->blocked)? _gf_false: _gf_true);
              gf_proc_dump_write(key, tmp);

              count++;
        }


}

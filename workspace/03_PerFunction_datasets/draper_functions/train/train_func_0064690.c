dht_statfs_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int op_ret, int op_errno, struct statvfs *statvfs, dict_t *xdata)
{
        dht_local_t *local         = NULL;
        int          this_call_cnt = 0;
        int          bsize         = 0;
        int          frsize        = 0;


        local = frame->local;

        LOCK (&frame->lock);
        {
                if (op_ret == -1) {
                        local->op_errno = op_errno;
                        goto unlock;
                }
                local->op_ret = 0;

                if (local->statvfs.f_bsize != 0) {
                        bsize = max(local->statvfs.f_bsize, statvfs->f_bsize);
                        frsize = max(local->statvfs.f_frsize, statvfs->f_frsize);
                        dht_normalize_stats(&local->statvfs, bsize, frsize);
                        dht_normalize_stats(statvfs, bsize, frsize);
                } else {
                        local->statvfs.f_bsize    = statvfs->f_bsize;
                        local->statvfs.f_frsize   = statvfs->f_frsize;
                }

                local->statvfs.f_blocks  += statvfs->f_blocks;
                local->statvfs.f_bfree   += statvfs->f_bfree;
                local->statvfs.f_bavail  += statvfs->f_bavail;
                local->statvfs.f_files   += statvfs->f_files;
                local->statvfs.f_ffree   += statvfs->f_ffree;
                local->statvfs.f_favail  += statvfs->f_favail;
                local->statvfs.f_fsid     = statvfs->f_fsid;
                local->statvfs.f_flag     = statvfs->f_flag;
                local->statvfs.f_namemax  = statvfs->f_namemax;

        }
unlock:
        UNLOCK (&frame->lock);


        this_call_cnt = dht_frame_return (frame);
        if (is_last_call (this_call_cnt))
                DHT_STACK_UNWIND (statfs, frame, local->op_ret, local->op_errno,
                                  &local->statvfs, xdata);

        return 0;
}

stripe_statfs_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct statvfs *stbuf)
{
        stripe_local_t *local = NULL;
        int32_t         callcnt = 0;

        if (!this || !frame || !frame->local) {
                gf_log ("stripe", GF_LOG_DEBUG, "possible NULL deref");
                goto out;
        }
        local = frame->local;

        LOCK(&frame->lock);
        {
                callcnt = --local->call_count;

                if (op_ret && (op_errno != ENOTCONN)) {
                        local->op_errno = op_errno;
                }
                if (op_ret == 0) {
                        struct statvfs *dict_buf = &local->statvfs_buf;
                        dict_buf->f_bsize   = stbuf->f_bsize;
                        dict_buf->f_frsize  = stbuf->f_frsize;
                        dict_buf->f_blocks += stbuf->f_blocks;
                        dict_buf->f_bfree  += stbuf->f_bfree;
                        dict_buf->f_bavail += stbuf->f_bavail;
                        dict_buf->f_files  += stbuf->f_files;
                        dict_buf->f_ffree  += stbuf->f_ffree;
                        dict_buf->f_favail += stbuf->f_favail;
                        dict_buf->f_fsid    = stbuf->f_fsid;
                        dict_buf->f_flag    = stbuf->f_flag;
                        dict_buf->f_namemax = stbuf->f_namemax;
                        local->op_ret = 0;
                }
        }
        UNLOCK (&frame->lock);

        if (!callcnt) {
                STRIPE_STACK_UNWIND (statfs, frame, local->op_ret,
                                     local->op_errno, &local->statvfs_buf);
        }
out:
        return 0;
}

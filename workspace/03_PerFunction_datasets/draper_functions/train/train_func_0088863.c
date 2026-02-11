syncop_statfs_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno,
                   struct statvfs *buf, dict_t *xdata)

{
        struct syncargs *args = NULL;

        args = cookie;

        args->op_ret   = op_ret;
        args->op_errno = op_errno;

        if (op_ret == 0) {
                args->statvfs_buf  = *buf;
        }

        __wake (args);

        return 0;
}

syncop_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iovec *vector,
                  int32_t count, struct iatt *stbuf, struct iobref *iobref)
{
        struct syncargs *args = NULL;

        args = cookie;

        INIT_LIST_HEAD (&args->entries.list);

        args->op_ret   = op_ret;
        args->op_errno = op_errno;

        if (args->op_ret >= 0) {
                if (iobref)
                        args->iobref = iobref_ref (iobref);
                args->vector = iov_dup (vector, count);
                args->count  = count;
        }

        __wake (args);

        return 0;

}

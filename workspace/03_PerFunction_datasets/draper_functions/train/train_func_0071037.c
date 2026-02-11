ioc_writev (call_frame_t *frame, xlator_t *this, fd_t *fd,
            struct iovec *vector, int32_t count, off_t offset,
            struct iobref *iobref)
{
        ioc_local_t *local     = NULL;
        uint64_t     ioc_inode = 0;

        local = GF_CALLOC (1, sizeof (ioc_local_t), gf_ioc_mt_ioc_local_t);
        if (local == NULL) {
                gf_log (this->name, GF_LOG_ERROR, "out of memory");

                STACK_UNWIND_STRICT (writev, frame, -1, ENOMEM, NULL, NULL);
                return 0;
        }


        local->fd = fd;
        frame->local = local;

        inode_ctx_get (fd->inode, this, &ioc_inode);
        if (ioc_inode)
                ioc_inode_flush ((ioc_inode_t *)(long)ioc_inode);

        STACK_WIND (frame, ioc_writev_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->writev, fd, vector, count, offset,
                    iobref);

        return 0;
}

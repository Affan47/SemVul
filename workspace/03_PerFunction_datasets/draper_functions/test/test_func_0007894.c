ra_fstat (call_frame_t *frame, xlator_t *this, fd_t *fd)
{
        ra_file_t *file     = NULL;
        fd_t      *iter_fd  = NULL;
        inode_t   *inode    = NULL;
        uint64_t   tmp_file = 0;
        int32_t    op_errno = EINVAL;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO (frame->this->name, this, unwind);
        GF_VALIDATE_OR_GOTO (frame->this->name, fd, unwind);

        inode = fd->inode;

        LOCK (&inode->lock);
        {
                list_for_each_entry (iter_fd, &inode->fd_list, inode_list) {
                        fd_ctx_get (iter_fd, this, &tmp_file);
                        file = (ra_file_t *)(long)tmp_file;

                        if (!file)
                                continue;
                        flush_region (frame, file, 0,
                                      file->pages.prev->offset + 1);
                }
        }
        UNLOCK (&inode->lock);

        STACK_WIND (frame, ra_attr_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->fstat, fd);
        return 0;

unwind:
        STACK_UNWIND_STRICT (stat, frame, -1, op_errno, NULL);
        return 0;
}

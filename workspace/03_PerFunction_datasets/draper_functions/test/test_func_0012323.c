ioc_open_cbk (call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
              int32_t op_errno, fd_t *fd, dict_t *xdata)
{
        uint64_t     tmp_ioc_inode = 0;
        ioc_local_t *local         = NULL;
        ioc_table_t *table         = NULL;
        ioc_inode_t *ioc_inode     = NULL;
        uint32_t     weight        = 0xffffffff;

        local = frame->local;
        if (!this || !this->private) {
                op_ret = -1;
                op_errno = EINVAL;
                goto out;
        }

        table = this->private;

        if (op_ret != -1) {
                inode_ctx_get (fd->inode, this, &tmp_ioc_inode);
                ioc_inode = (ioc_inode_t *)(long)tmp_ioc_inode;

                ioc_table_lock (ioc_inode->table);
                {
                        list_move_tail (&ioc_inode->inode_lru,
                                        &table->inode_lru[ioc_inode->weight]);
                }
                ioc_table_unlock (ioc_inode->table);

                ioc_inode_lock (ioc_inode);
                {
                        if ((table->min_file_size > ioc_inode->ia_size)
                            || ((table->max_file_size > 0)
                                && (table->max_file_size < ioc_inode->ia_size))) {
                                fd_ctx_set (fd, this, 1);
                        }
                }
                ioc_inode_unlock (ioc_inode);


                if ((local->flags & O_DIRECT)){


                        fd_ctx_set (fd, this, 1);
                }


                if (weight == 0) {


                        fd_ctx_set (fd, this, 1);
                }
        }

out:
        mem_put (local);
        frame->local = NULL;

        STACK_UNWIND_STRICT (open, frame, op_ret, op_errno, fd, xdata);

        return 0;
}

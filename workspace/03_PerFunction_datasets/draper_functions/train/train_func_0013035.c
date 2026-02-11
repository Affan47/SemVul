__fd_create (inode_t *inode, uint64_t pid)
{
        fd_t *fd = NULL;

        if (inode == NULL) {
                gf_log_callingfn ("fd", GF_LOG_ERROR, "invalid argument");
                return NULL;
        }

        fd = mem_get0 (inode->table->fd_mem_pool);
        if (!fd)
                goto out;

        fd->xl_count = inode->table->xl->graph->xl_count + 1;

        fd->_ctx = GF_CALLOC (1, (sizeof (struct _fd_ctx) * fd->xl_count),
                              gf_common_mt_fd_ctx);
        if (!fd->_ctx)
                goto free_fd;

        fd->lk_ctx = fd_lk_ctx_create ();
        if (!fd->lk_ctx)
                goto free_fd_ctx;

        fd->inode = inode_ref (inode);
        fd->pid = pid;
        INIT_LIST_HEAD (&fd->inode_list);

        LOCK_INIT (&fd->lock);
out:
        return fd;

free_fd_ctx:
        GF_FREE (fd->_ctx);
free_fd:
        mem_put (fd);

        return NULL;
}

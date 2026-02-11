sp_get_cache_inode (xlator_t *this, inode_t *inode, int32_t pid)
{
        fd_t       *fd    = NULL;
        sp_cache_t *cache = NULL;

        if (inode == NULL) {
                goto out;
        }

        fd = fd_lookup (inode, pid);
        if (fd == NULL) {
                goto out;
        }

        cache = sp_get_cache_fd (this, fd);

        fd_unref (fd);
out:
        return cache;
}

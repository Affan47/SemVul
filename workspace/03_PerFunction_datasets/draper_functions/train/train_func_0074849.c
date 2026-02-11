sp_readdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, gf_dirent_t *entries)
{
        sp_local_t      *local       = NULL;
        sp_cache_t      *cache       = NULL;
        fd_t            *fd          = NULL;
        int32_t          ret         = 0;
        char             was_present = 1;
        sp_private_t    *priv        = NULL;

        GF_ASSERT (frame);
        if (op_ret == -1) {
                goto out;
        }

        if ((this == NULL) || (this->private == NULL)) {
                gf_log (frame->this->name, GF_LOG_WARNING,
                        (this == NULL) ? "xlator object (this) is NULL"
                        : "stat-prefetch configuration (this->private) is "
                        "NULL");
                op_ret = -1;
                op_errno = EINVAL;
                goto out;
        }

        local = frame->local;
        if (local == NULL) {
                gf_log (frame->this->name, GF_LOG_WARNING, "local is NULL");
                op_ret = -1;
                op_errno = EINVAL;
                goto out;
        }

        fd = local->fd;

        priv = this->private;

        LOCK (&priv->lock);
        {
                if (!priv->mem_pool)
                        priv->mem_pool =  mem_pool_new (rbthash_entry_t,
                                                        GF_SP_CACHE_ENTRIES_EXPECTED);
        }
        UNLOCK (&priv->lock);

        if (!priv->mem_pool)
                goto out;

        LOCK (&fd->lock);
        {
                cache = __sp_get_cache_fd (this, fd);
                if (cache == NULL) {
                        was_present = 0;
                        cache = sp_cache_init (this);
                        if (cache == NULL) {
                                gf_log (this->name, GF_LOG_WARNING,
                                        "creation of stat-prefetch cache "
                                        "for fd (%p) opened on inode "
                                        "(gfid:%s) failed", fd,
                                        uuid_utoa (fd->inode->gfid));
                                goto unlock;
                        }

                        ret = __sp_put_cache (this, fd, cache);
                        if (ret == -1) {
                                sp_cache_free (cache);
                                gf_log (this->name, GF_LOG_WARNING,
                                        "cannot store cache in fd (%p) opened "
                                        "on inode (gfid:%s)", fd,
                                        uuid_utoa (fd->inode->gfid));
                                goto unlock;
                        }
                }

                sp_cache_ref (cache);
        }
unlock:
        UNLOCK (&fd->lock);

        if (cache != NULL) {
                sp_cache_add_entries (cache, entries);
                if (was_present) {
                        sp_cache_unref (cache);
                }
        }

out:
        SP_STACK_UNWIND (readdir, frame, op_ret, op_errno, entries);
        return 0;
}

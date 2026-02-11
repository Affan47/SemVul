fuse_migrate_locks (xlator_t *this, fd_t *basefd, fd_t *oldfd,
                    xlator_t *old_subvol, xlator_t *new_subvol)
{
        int	 ret      = -1;
        dict_t	*lockinfo = NULL;
        void    *ptr      = NULL;
	fd_t    *newfd    = NULL;
        fuse_fd_ctx_t *basefd_ctx         = NULL;


	if (!oldfd->lk_ctx || fd_lk_ctx_empty (oldfd->lk_ctx))
		return 0;

        basefd_ctx = fuse_fd_ctx_get (this, basefd);
        GF_VALIDATE_OR_GOTO ("glusterfs-fuse", basefd_ctx, out);

        LOCK (&basefd->lock);
        {
                newfd = fd_ref (basefd_ctx->activefd);
        }
        UNLOCK (&basefd->lock);

        ret = syncop_fgetxattr (old_subvol, oldfd, &lockinfo,
                                GF_XATTR_LOCKINFO_KEY);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_WARNING,
			"getting lockinfo failed while migrating locks"
			"(oldfd:%p newfd:%p inode-gfid:%s)"
			"(old-subvol:%s-%d new-subvol:%s-%d)",
			oldfd, newfd, uuid_utoa (newfd->inode->gfid),
			old_subvol->name, old_subvol->graph->id,
			new_subvol->name, new_subvol->graph->id);
                goto out;
        }

        ret = dict_get_ptr (lockinfo, GF_XATTR_LOCKINFO_KEY, &ptr);
        if (ptr == NULL) {
                ret = 0;
                gf_log (this->name, GF_LOG_INFO,
                        "No lockinfo present on any of the bricks "
			"(oldfd: %p newfd:%p inode-gfid:%s) "
                        "(old-subvol:%s-%d new-subvol:%s-%d)",
			oldfd, newfd, uuid_utoa (newfd->inode->gfid),
			old_subvol->name, old_subvol->graph->id,
			new_subvol->name, new_subvol->graph->id);

                goto out;
        }

        ret = syncop_fsetxattr (new_subvol, newfd, lockinfo, 0);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_WARNING,
			"migrating locks failed (oldfd:%p newfd:%p "
			"inode-gfid:%s) (old-subvol:%s-%d new-subvol:%s-%d)",
			oldfd, newfd, uuid_utoa (newfd->inode->gfid),
			old_subvol->name, old_subvol->graph->id,
			new_subvol->name, new_subvol->graph->id);
                goto out;
        }

out:
	if (newfd)
		fd_unref (newfd);

        if (lockinfo != NULL) {
                dict_unref (lockinfo);
        }

        return ret;
}

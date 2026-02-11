__glfs_resolve_fd (struct glfs *fs, xlator_t *subvol, struct glfs_fd *glfd)
{
	fd_t *fd = NULL;

	if (glfd->fd->inode->table->xl == subvol)
		return fd_ref (glfd->fd);

	fd = __glfs_migrate_fd (fs, subvol, glfd);
	if (!fd)
		return NULL;

	if (subvol == fs->active_subvol) {
		fd_unref (glfd->fd);
		glfd->fd = fd_ref (fd);
	}

	return fd;
}

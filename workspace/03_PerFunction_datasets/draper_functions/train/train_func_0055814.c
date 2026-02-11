glfs_fsetattr (struct glfs_fd *glfd, struct iatt *iatt, int valid)
{
	int              ret = -1;
	xlator_t        *subvol = NULL;
	fd_t            *fd = NULL;

	__glfs_entry_fd (glfd);

	subvol = glfs_active_subvol (glfd->fs);
	if (!subvol) {
		ret = -1;
		errno = EIO;
		goto out;
	}

	fd = glfs_resolve_fd (glfd->fs, subvol, glfd);
	if (!fd) {
		ret = -1;
		errno = EBADFD;
		goto out;
	}

	ret = syncop_fsetattr (subvol, fd, iatt, valid, 0, 0);
out:
	if (fd)
		fd_unref (fd);

	glfs_subvol_done (glfd->fs, subvol);

	return ret;
}

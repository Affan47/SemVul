glfs_h_open (struct glfs *fs, struct glfs_object *object, int flags)
{
	int              ret = -1;
	struct glfs_fd  *glfd = NULL;
	xlator_t        *subvol = NULL;
	inode_t         *inode = NULL;
	loc_t            loc = {0, };


	if ((fs == NULL) || (object == NULL)) {
		errno = EINVAL;
		return NULL;
	}

	__glfs_entry_fs (fs);


	subvol = glfs_active_subvol (fs);
	if (!subvol) {
		errno = EIO;
		goto out;
	}


	inode = glfs_resolve_inode (fs, subvol, object);
	if (!inode) {
		errno = ESTALE;
		goto out;
	}


	if (IA_ISDIR (inode->ia_type)) {
		ret = -1;
		errno = EISDIR;
		goto out;
	}

	if (!IA_ISREG (inode->ia_type)) {
		ret = -1;
		errno = EINVAL;
		goto out;
	}

	glfd = glfs_fd_new (fs);
	if (!glfd) {
		errno = ENOMEM;
		goto out;
	}

	glfd->fd = fd_create (inode, getpid());
	if (!glfd->fd) {
		ret = -1;
		errno = ENOMEM;
		goto out;
	}


	GLFS_LOC_FILL_INODE (inode, loc, out);


	ret = syncop_open (subvol, &loc, flags, glfd->fd);

out:
	loc_wipe (&loc);

	if (inode)
		inode_unref (inode);

	if (ret && glfd) {
		glfs_fd_destroy (glfd);
		glfd = NULL;
	} else {
		glfd->fd->flags = flags;
		fd_bind (glfd->fd);
		glfs_fd_bind (glfd);
	}

	glfs_subvol_done (fs, subvol);

	return glfd;
}

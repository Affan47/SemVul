glfs_h_link (struct glfs *fs, struct glfs_object *linksrc,
	     struct glfs_object *parent, const char *name)
{
	int                 ret = -1;
	xlator_t           *subvol = NULL;
	inode_t            *inode = NULL;
	inode_t            *pinode = NULL;
	loc_t               oldloc = {0, };
	loc_t               newloc = {0, };


	if ((fs == NULL) || (linksrc == NULL) || (parent == NULL) ||
		(name == NULL)) {
		errno = EINVAL;
		return -1;
	}

	__glfs_entry_fs (fs);


	subvol = glfs_active_subvol (fs);
	if (!subvol) {
		ret = -1;
		errno = EIO;
		goto out;
	}


	inode = glfs_resolve_inode (fs, subvol, linksrc);
	if (!inode) {
		errno = ESTALE;
		goto out;
	}

	if (inode->ia_type == IA_IFDIR) {
		ret = -1;
		errno = EISDIR;
		goto out;
	}

	GLFS_LOC_FILL_INODE (inode, oldloc, out);


	pinode = glfs_resolve_inode (fs, subvol, parent);
	if (!pinode) {
		errno = ESTALE;
		goto out;
	}


	newloc.parent = inode_ref (pinode);
	newloc.name = name;
	ret = glfs_loc_touchup (&newloc);
	if (ret != 0) {
		errno = EINVAL;
		goto out;
	}


	newloc.inode = inode_ref (inode);


	ret = syncop_link (subvol, &oldloc, &newloc);

	if (ret == 0)

		ret = glfs_loc_link (&newloc, NULL);
out:
	loc_wipe (&oldloc);
	loc_wipe (&newloc);

	if (inode)
		inode_unref (inode);

	if (pinode)
		inode_unref (pinode);

	glfs_subvol_done (fs, subvol);

	return ret;
}

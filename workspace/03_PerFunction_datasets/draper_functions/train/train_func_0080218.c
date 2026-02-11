glfs_loc_link (loc_t *loc, struct iatt *iatt)
{
	int ret = -1;
	inode_t *linked_inode = NULL;

	if (!loc->inode) {
		errno = EINVAL;
		return -1;
	}

	linked_inode = inode_link (loc->inode, loc->parent, loc->name, iatt);
	if (linked_inode) {
		inode_lookup (linked_inode);
		inode_unref (linked_inode);
		ret = 0;
	} else {
		ret = -1;
		errno = ENOMEM;
	}

	return ret;
}

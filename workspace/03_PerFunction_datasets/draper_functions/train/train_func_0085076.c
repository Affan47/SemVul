reiserfs_find_actor(struct inode *inode, void *opaque)
{
	struct reiserfs_iget_args *args;

	args = opaque;

	return (inode->i_ino == args->objectid) &&
	    (le32_to_cpu(INODE_PKEY(inode)->k_dir_id) == args->dirid);
}

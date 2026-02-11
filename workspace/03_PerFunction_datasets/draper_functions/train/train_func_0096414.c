dlmfs_get_inode(struct inode *parent,
				     struct dentry *dentry,
				     umode_t mode)
{
	struct super_block *sb = parent->i_sb;
	struct inode * inode = new_inode(sb);
	struct dlmfs_inode_private *ip;

	if (!inode)
		return NULL;

	inode->i_ino = get_next_ino();
	inode_init_owner(inode, parent, mode);
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

	ip = DLMFS_I(inode);
	ip->ip_conn = DLMFS_I(parent)->ip_conn;

	switch (mode & S_IFMT) {
	default:


		BUG();
		break;
	case S_IFREG:
		inode->i_op = &dlmfs_file_inode_operations;
		inode->i_fop = &dlmfs_file_operations;

		i_size_write(inode,  DLM_LVB_LEN);

		user_dlm_lock_res_init(&ip->ip_lockres, dentry);


		ip->ip_parent = igrab(parent);
		BUG_ON(!ip->ip_parent);
		break;
	case S_IFDIR:
		inode->i_op = &dlmfs_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;


		inc_nlink(inode);
		break;
	}
	return inode;
}

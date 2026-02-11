f2fs_get_parent(struct dentry *child)
{
	struct qstr dotdot = QSTR_INIT("..", 2);
	unsigned long ino = f2fs_inode_by_name(d_inode(child), &dotdot);
	if (!ino)
		return ERR_PTR(-ENOENT);
	return d_obtain_alias(f2fs_iget(d_inode(child)->i_sb, ino));
}

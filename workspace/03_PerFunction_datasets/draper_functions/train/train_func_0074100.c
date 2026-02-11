nilfs_get_dentry(struct super_block *sb, u64 cno,
				       u64 ino, u32 gen)
{
	struct nilfs_root *root;
	struct inode *inode;

	if (ino < NILFS_FIRST_INO(sb) && ino != NILFS_ROOT_INO)
		return ERR_PTR(-ESTALE);

	root = nilfs_lookup_root(sb->s_fs_info, cno);
	if (!root)
		return ERR_PTR(-ESTALE);

	inode = nilfs_iget(sb, root, ino);
	nilfs_put_root(root);

	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (gen && inode->i_generation != gen) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}
	return d_obtain_alias(inode);
}

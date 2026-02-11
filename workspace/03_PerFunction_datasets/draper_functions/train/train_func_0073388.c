nilfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;
	struct nilfs_transaction_info ti;
	int err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	if (err)
		return err;

	inc_nlink(dir);

	inode = nilfs_new_inode(dir, S_IFDIR | mode);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_dir;

	inode->i_op = &nilfs_dir_inode_operations;
	inode->i_fop = &nilfs_dir_operations;
	inode->i_mapping->a_ops = &nilfs_aops;

	inc_nlink(inode);

	err = nilfs_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = nilfs_add_link(dentry, inode);
	if (err)
		goto out_fail;

	nilfs_mark_inode_dirty(inode);
	d_instantiate(dentry, inode);
	unlock_new_inode(inode);
out:
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;

out_fail:
	drop_nlink(inode);
	drop_nlink(inode);
	nilfs_mark_inode_dirty(inode);
	unlock_new_inode(inode);
	iput(inode);
out_dir:
	drop_nlink(dir);
	nilfs_mark_inode_dirty(dir);
	goto out;
}

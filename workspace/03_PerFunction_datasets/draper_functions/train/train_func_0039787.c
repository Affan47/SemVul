ufs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry)
{
	struct inode *old_inode = d_inode(old_dentry);
	struct inode *new_inode = d_inode(new_dentry);
	struct page *dir_page = NULL;
	struct ufs_dir_entry * dir_de = NULL;
	struct page *old_page;
	struct ufs_dir_entry *old_de;
	int err = -ENOENT;

	old_de = ufs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	if (!old_de)
		goto out;

	if (S_ISDIR(old_inode->i_mode)) {
		err = -EIO;
		dir_de = ufs_dotdot(old_inode, &dir_page);
		if (!dir_de)
			goto out_old;
	}

	if (new_inode) {
		struct page *new_page;
		struct ufs_dir_entry *new_de;

		err = -ENOTEMPTY;
		if (dir_de && !ufs_empty_dir(new_inode))
			goto out_dir;

		err = -ENOENT;
		new_de = ufs_find_entry(new_dir, &new_dentry->d_name, &new_page);
		if (!new_de)
			goto out_dir;
		ufs_set_link(new_dir, new_de, new_page, old_inode, 1);
		new_inode->i_ctime = CURRENT_TIME_SEC;
		if (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	} else {
		err = ufs_add_link(new_dentry, old_inode);
		if (err)
			goto out_dir;
		if (dir_de)
			inode_inc_link_count(new_dir);
	}


	old_inode->i_ctime = CURRENT_TIME_SEC;

	ufs_delete_entry(old_dir, old_de, old_page);
	mark_inode_dirty(old_inode);

	if (dir_de) {
		if (old_dir != new_dir)
			ufs_set_link(old_inode, dir_de, dir_page, new_dir, 0);
		else {
			kunmap(dir_page);
			page_cache_release(dir_page);
		}
		inode_dec_link_count(old_dir);
	}
	return 0;


out_dir:
	if (dir_de) {
		kunmap(dir_page);
		page_cache_release(dir_page);
	}
out_old:
	kunmap(old_page);
	page_cache_release(old_page);
out:
	return err;
}

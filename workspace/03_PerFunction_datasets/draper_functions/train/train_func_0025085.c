sel_make_dir(struct dentry *dir, const char *name,
			unsigned long *ino)
{
	struct dentry *dentry = d_alloc_name(dir, name);
	struct inode *inode;

	if (!dentry)
		return ERR_PTR(-ENOMEM);

	inode = sel_make_inode(dir->d_sb, S_IFDIR | S_IRUGO | S_IXUGO);
	if (!inode) {
		dput(dentry);
		return ERR_PTR(-ENOMEM);
	}

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	inode->i_ino = ++(*ino);

	inc_nlink(inode);
	d_add(dentry, inode);

	inc_nlink(d_inode(dir));

	return dentry;
}

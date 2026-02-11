security_d_instantiate(struct dentry *dentry, struct inode *inode)
{
	if (unlikely(inode && IS_PRIVATE(inode)))
		return;
	call_void_hook(d_instantiate, dentry, inode);
}

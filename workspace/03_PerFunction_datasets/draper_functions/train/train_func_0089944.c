security_inode_follow_link(struct dentry *dentry, struct inode *inode,
			       bool rcu)
{
	if (unlikely(IS_PRIVATE(inode)))
		return 0;
	return call_int_hook(inode_follow_link, 0, dentry, inode, rcu);
}

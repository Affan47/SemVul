au_dpri_dalias(struct inode *inode)
{
	struct dentry *d;

	spin_lock(&inode->i_lock);
	hlist_for_each_entry(d, &inode->i_dentry, d_u.d_alias)
		au_dpri_dentry(d);
	spin_unlock(&inode->i_lock);
}

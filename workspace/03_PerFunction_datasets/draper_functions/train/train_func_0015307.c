ncp_compare_dentry(const struct dentry *parent, const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	struct inode *pinode;

	if (len != name->len)
		return 1;

	pinode = d_inode_rcu(parent);
	if (!pinode)
		return 1;

	if (ncp_case_sensitive(pinode))
		return strncmp(str, name->name, len);

	return ncp_strnicmp(NCP_IO_TABLE(pinode->i_sb), str, name->name, len);
}

ns_rmdir_op(struct inode *dir, struct dentry *dentry)
{
	struct aa_ns *ns, *parent;

	struct aa_label *label = aa_begin_current_label(DO_UPDATE);
	int error = aa_may_manage_policy(label, NULL, AA_MAY_LOAD_POLICY);
	aa_end_current_label(label);
	if (error)
		return error;

	 parent = aa_get_ns(dir->i_private);


	inode_unlock(dir);
	inode_unlock(dentry->d_inode);

	mutex_lock(&parent->lock);
	ns = aa_get_ns(__aa_findn_ns(&parent->sub_ns, dentry->d_name.name,
				     dentry->d_name.len));
	if (!ns) {
		error = -ENOENT;
		goto out;
	}
	AA_BUG(ns_dir(ns) != dentry);

	__aa_remove_ns(ns);
	aa_put_ns(ns);

out:
	mutex_unlock(&parent->lock);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	inode_lock(dentry->d_inode);
	aa_put_ns(parent);

	return error;
}

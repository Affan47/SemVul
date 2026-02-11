au_srxattr(struct dentry *dentry, struct au_srxattr *arg)
{
	int err;
	struct path h_path;
	struct super_block *sb;
	struct au_icpup_args *a;
	struct inode *inode, *h_inode;

	inode = d_inode(dentry);
	IMustLock(inode);

	err = -ENOMEM;
	a = kzalloc(sizeof(*a), GFP_NOFS);
	if (unlikely(!a))
		goto out;

	sb = dentry->d_sb;
	err = si_read_lock(sb, AuLock_FLUSH | AuLock_NOPLM);
	if (unlikely(err))
		goto out_kfree;

	h_path.dentry = NULL;
	di_write_lock_child(dentry);
	err = au_h_path_to_set_attr(dentry, a, &h_path);
	if (unlikely(err))
		goto out_di;

	mutex_unlock(&a->h_inode->i_mutex);
	switch (arg->type) {
	case AU_XATTR_SET:
		err = vfsub_setxattr(h_path.dentry,
				     arg->u.set.name, arg->u.set.value,
				     arg->u.set.size, arg->u.set.flags);
		break;
	case AU_XATTR_REMOVE:
		err = vfsub_removexattr(h_path.dentry, arg->u.remove.name);
		break;
	case AU_ACL_SET:
		err = -EOPNOTSUPP;
		h_inode = d_inode(h_path.dentry);
		if (h_inode->i_op->set_acl)
			err = h_inode->i_op->set_acl(h_inode,
						     arg->u.acl_set.acl,
						     arg->u.acl_set.type);
		break;
	}
	if (!err)
		au_cpup_attr_timesizes(inode);

	au_unpin(&a->pin);
	if (unlikely(err))
		au_update_dbstart(dentry);

out_di:
	di_write_unlock(dentry);
	si_read_unlock(sb);
out_kfree:
	kfree(a);
out:
	AuTraceErr(err);
	return err;
}

aufs_follow_link(struct dentry *dentry, void **cookie)
{
	const char *ret;
	struct inode *inode, *h_inode;
	struct dentry *h_dentry;
	struct au_symlink *slink;
	int err;
	aufs_bindex_t bindex;

	ret = NULL;
	err = aufs_read_lock(dentry, AuLock_IR | AuLock_GEN);
	if (unlikely(err))
		goto out;

	err = au_d_hashed_positive(dentry);
	if (unlikely(err))
		goto out_unlock;

	err = -EINVAL;
	inode = d_inode(dentry);
	bindex = au_ibstart(inode);
	h_inode = au_h_iptr(inode, bindex);
	if (unlikely(!h_inode->i_op->follow_link))
		goto out_unlock;

	err = -ENOMEM;
	slink = kmalloc(sizeof(*slink), GFP_NOFS);
	if (unlikely(!slink))
		goto out_unlock;

	err = -EBUSY;
	h_dentry = NULL;
	if (au_dbstart(dentry) <= bindex) {
		h_dentry = au_h_dptr(dentry, bindex);
		if (h_dentry)
			dget(h_dentry);
	}
	if (!h_dentry) {
		h_dentry = d_find_any_alias(h_inode);
		if (IS_ERR(h_dentry)) {
			err = PTR_ERR(h_dentry);
			goto out_free;
		}
	}
	if (unlikely(!h_dentry))
		goto out_free;

	err = 0;
	AuDbg("%pf\n", h_inode->i_op->follow_link);
	AuDbgDentry(h_dentry);
	ret = h_inode->i_op->follow_link(h_dentry, cookie);
	dput(h_dentry);

	if (!IS_ERR_OR_NULL(ret)) {
		au_symlink_add(inode->i_sb, slink, h_inode, *cookie);
		*cookie = slink;
		AuDbg("slink %p\n", slink);
		goto out_unlock;
	}

out_free:
	slink->h_inode = NULL;
	kfree_rcu(slink, rcu);
out_unlock:
	aufs_read_unlock(dentry, AuLock_IR);
out:
	if (unlikely(err))
		ret = ERR_PTR(err);
	AuTraceErrPtr(ret);
	return ret;
}

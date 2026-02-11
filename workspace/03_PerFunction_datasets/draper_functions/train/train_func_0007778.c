autofs4_expire_indirect(struct super_block *sb,
				       struct vfsmount *mnt,
				       struct autofs_sb_info *sbi,
				       int how)
{
	unsigned long timeout;
	struct dentry *root = sb->s_root;
	struct dentry *dentry;
	struct dentry *expired;
	struct dentry *found;
	struct autofs_info *ino;

	if (!root)
		return NULL;

	now = jiffies;
	timeout = sbi->exp_timeout;

	dentry = NULL;
	while ((dentry = get_next_positive_subdir(dentry, root))) {
		int flags = how;

		spin_lock(&sbi->fs_lock);
		ino = autofs4_dentry_ino(dentry);
		if (ino->flags & AUTOFS_INF_WANT_EXPIRE) {
			spin_unlock(&sbi->fs_lock);
			continue;
		}
		spin_unlock(&sbi->fs_lock);

		expired = should_expire(dentry, mnt, timeout, flags);
		if (!expired)
			continue;

		spin_lock(&sbi->fs_lock);
		ino = autofs4_dentry_ino(expired);
		ino->flags |= AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
		synchronize_rcu();


		flags &= ~AUTOFS_EXP_LEAVES;
		found = should_expire(expired, mnt, timeout, how);
		if (!found || found != expired)

			goto next;

		if (expired != dentry)
			dput(dentry);

		spin_lock(&sbi->fs_lock);
		goto found;
next:
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_WANT_EXPIRE;
		spin_unlock(&sbi->fs_lock);
		if (expired != dentry)
			dput(expired);
	}
	return NULL;

found:
	DPRINTK("returning %p %pd", expired, expired);
	ino->flags |= AUTOFS_INF_EXPIRING;
	init_completion(&ino->expire_complete);
	spin_unlock(&sbi->fs_lock);
	return expired;
}

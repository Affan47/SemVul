jfs_link(struct dentry *old_dentry,
	     struct inode *dir, struct dentry *dentry)
{
	int rc;
	tid_t tid;
	struct inode *ip = d_inode(old_dentry);
	ino_t ino;
	struct component_name dname;
	struct btstack btstack;
	struct inode *iplist[2];

	jfs_info("jfs_link: %pd %pd", old_dentry, dentry);

	rc = dquot_initialize(dir);
	if (rc)
		goto out;

	tid = txBegin(ip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);


	if ((rc = get_UCSname(&dname, dentry)))
		goto out_tx;

	if ((rc = dtSearch(dir, &dname, &ino, &btstack, JFS_CREATE)))
		goto free_dname;


	ino = ip->i_ino;
	if ((rc = dtInsert(tid, dir, &dname, &ino, &btstack)))
		goto free_dname;


	inc_nlink(ip);
	ip->i_ctime = CURRENT_TIME;
	dir->i_ctime = dir->i_mtime = CURRENT_TIME;
	mark_inode_dirty(dir);
	ihold(ip);

	iplist[0] = ip;
	iplist[1] = dir;
	rc = txCommit(tid, 2, &iplist[0], 0);

	if (rc) {
		drop_nlink(ip);
		iput(ip);
	} else
		d_instantiate(dentry, ip);

      free_dname:
	free_UCSname(&dname);

      out_tx:
	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dir)->commit_mutex);

      out:
	jfs_info("jfs_link: rc:%d", rc);
	return rc;
}

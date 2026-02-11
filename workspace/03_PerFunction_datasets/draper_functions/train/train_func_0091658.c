mknod_ptmx(struct super_block *sb)
{
	int mode;
	int rc = -ENOMEM;
	struct dentry *dentry;
	struct inode *inode;
	struct dentry *root = sb->s_root;
	struct pts_fs_info *fsi = DEVPTS_SB(sb);
	struct pts_mount_opts *opts = &fsi->mount_opts;
	kuid_t root_uid;
	kgid_t root_gid;

	root_uid = make_kuid(current_user_ns(), 0);
	root_gid = make_kgid(current_user_ns(), 0);
	if (!uid_valid(root_uid) || !gid_valid(root_gid))
		return -EINVAL;

	mutex_lock(&d_inode(root)->i_mutex);


	if (fsi->ptmx_dentry) {
		rc = 0;
		goto out;
	}

	dentry = d_alloc_name(root, "ptmx");
	if (!dentry) {
		pr_err("Unable to alloc dentry for ptmx node\n");
		goto out;
	}


	inode = new_inode(sb);
	if (!inode) {
		pr_err("Unable to alloc inode for ptmx node\n");
		dput(dentry);
		goto out;
	}

	inode->i_ino = 2;
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;

	mode = S_IFCHR|opts->ptmxmode;
	init_special_inode(inode, mode, MKDEV(TTYAUX_MAJOR, 2));
	inode->i_uid = root_uid;
	inode->i_gid = root_gid;

	d_add(dentry, inode);

	fsi->ptmx_dentry = dentry;
	rc = 0;
out:
	mutex_unlock(&d_inode(root)->i_mutex);
	return rc;
}

vfat_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct super_block *sb = dir->i_sb;
	struct inode *inode;
	struct fat_slot_info sinfo;
	struct timespec ts;
	int err, cluster;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	ts = CURRENT_TIME_SEC;
	cluster = fat_alloc_new_dir(dir, &ts);
	if (cluster < 0) {
		err = cluster;
		goto out;
	}
	err = vfat_add_entry(dir, &dentry->d_name, 1, cluster, &ts, &sinfo);
	if (err)
		goto out_free;
	dir->i_version++;
	inc_nlink(dir);

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brelse(sinfo.bh);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);

		goto out;
	}
	inode->i_version++;
	set_nlink(inode, 2);
	inode->i_mtime = inode->i_atime = inode->i_ctime = ts;


	d_instantiate(dentry, inode);

	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	return 0;

out_free:
	fat_free_clusters(dir, cluster);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	return err;
}

hfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct hfs_sb_info *sbi;
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct inode *root_inode;
	int res;

	sbi = kzalloc(sizeof(struct hfs_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sbi->sb = sb;
	sb->s_fs_info = sbi;
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->mdb_work, flush_mdb);

	res = -EINVAL;
	if (!parse_options((char *)data, sbi)) {
		pr_err("unable to parse mount options\n");
		goto bail;
	}

	sb->s_op = &hfs_super_operations;
	sb->s_flags |= MS_NODIRATIME;
	mutex_init(&sbi->bitmap_lock);

	res = hfs_mdb_get(sb);
	if (res) {
		if (!silent)
			pr_warn("can't find a HFS filesystem on dev %s\n",
				hfs_mdb_name(sb));
		res = -EINVAL;
		goto bail;
	}


	res = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	if (res)
		goto bail_no_root;
	res = hfs_cat_find_brec(sb, HFS_ROOT_CNID, &fd);
	if (!res) {
		if (fd.entrylength > sizeof(rec) || fd.entrylength < 0) {
			res =  -EIO;
			goto bail;
		}
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset, fd.entrylength);
	}
	if (res) {
		hfs_find_exit(&fd);
		goto bail_no_root;
	}
	res = -EINVAL;
	root_inode = hfs_iget(sb, &fd.search_key->cat, &rec);
	hfs_find_exit(&fd);
	if (!root_inode)
		goto bail_no_root;

	sb->s_d_op = &hfs_dentry_operations;
	res = -ENOMEM;
	sb->s_root = d_make_root(root_inode);
	if (!sb->s_root)
		goto bail_no_root;


	return 0;

bail_no_root:
	pr_err("get root inode failed\n");
bail:
	hfs_mdb_put(sb);
	return res;
}

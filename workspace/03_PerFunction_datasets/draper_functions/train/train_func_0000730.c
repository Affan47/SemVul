ncp_iget(struct super_block *sb, struct ncp_entry_info *info)
{
	struct inode *inode;

	if (info == NULL) {
		pr_err("%s: info is NULL\n", __func__);
		return NULL;
	}

	inode = new_inode(sb);
	if (inode) {
		atomic_set(&NCP_FINFO(inode)->opened, info->opened);

		inode->i_ino = info->ino;
		ncp_set_attr(inode, info);
		if (S_ISREG(inode->i_mode)) {
			inode->i_op = &ncp_file_inode_operations;
			inode->i_fop = &ncp_file_operations;
		} else if (S_ISDIR(inode->i_mode)) {
			inode->i_op = &ncp_dir_inode_operations;
			inode->i_fop = &ncp_dir_operations;
#ifdef CONFIG_NCPFS_NFS_NS
		} else if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) || S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
			init_special_inode(inode, inode->i_mode,
				new_decode_dev(info->i.nfs.rdev));
#endif
#if defined(CONFIG_NCPFS_EXTRAS) || defined(CONFIG_NCPFS_NFS_NS)
		} else if (S_ISLNK(inode->i_mode)) {
			inode->i_op = &ncp_symlink_inode_operations;
			inode->i_data.a_ops = &ncp_symlink_aops;
#endif
		} else {
			make_bad_inode(inode);
		}
		insert_inode_hash(inode);
	} else
		pr_err("%s: iget failed!\n", __func__);
	return inode;
}

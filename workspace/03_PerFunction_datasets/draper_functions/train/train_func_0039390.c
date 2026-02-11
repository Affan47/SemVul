__nilfs_read_inode(struct super_block *sb,
			      struct nilfs_root *root, unsigned long ino,
			      struct inode *inode)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct buffer_head *bh;
	struct nilfs_inode *raw_inode;
	int err;

	down_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	err = nilfs_ifile_get_inode_block(root->ifile, ino, &bh);
	if (unlikely(err))
		goto bad_inode;

	raw_inode = nilfs_ifile_map_inode(root->ifile, ino, bh);

	err = nilfs_read_inode_common(inode, raw_inode);
	if (err)
		goto failed_unmap;

	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &nilfs_file_inode_operations;
		inode->i_fop = &nilfs_file_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &nilfs_dir_inode_operations;
		inode->i_fop = &nilfs_dir_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		inode->i_op = &nilfs_symlink_inode_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	} else {
		inode->i_op = &nilfs_special_inode_operations;
		init_special_inode(
			inode, inode->i_mode,
			huge_decode_dev(le64_to_cpu(raw_inode->i_device_code)));
	}
	nilfs_ifile_unmap_inode(root->ifile, ino, bh);
	brelse(bh);
	up_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	nilfs_set_inode_flags(inode);
	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_constraint(inode->i_mapping, ~__GFP_FS));
	return 0;

 failed_unmap:
	nilfs_ifile_unmap_inode(root->ifile, ino, bh);
	brelse(bh);

 bad_inode:
	up_read(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	return err;
}

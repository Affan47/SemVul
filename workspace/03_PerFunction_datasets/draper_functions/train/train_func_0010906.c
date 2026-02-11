free_full_branch(struct inode *inode, u64 ind_block, int depth)
{
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	struct ufs_buffer_head *ubh = ubh_bread(sb, ind_block, uspi->s_bsize);
	unsigned i;

	if (!ubh)
		return;

	if (--depth) {
		for (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			if (block)
				free_full_branch(inode, block, depth);
		}
	} else {
		struct to_free ctx = {.inode = inode};

		for (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			if (block)
				free_data(&ctx, block, uspi->s_fpb);
		}
		free_data(&ctx, 0, 0);
	}

	ubh_bforget(ubh);
	ufs_free_blocks(inode, ind_block, uspi->s_fpb);
}

efs_get_block(struct inode *inode, sector_t iblock,
		  struct buffer_head *bh_result, int create)
{
	int error = -EROFS;
	long phys;

	if (create)
		return error;
	if (iblock >= inode->i_blocks) {
#ifdef DEBUG


		pr_warn("%s(): block %d >= %ld (filesize %ld)\n",
			__func__, block, inode->i_blocks, inode->i_size);
#endif
		return 0;
	}
	phys = efs_map_block(inode, iblock);
	if (phys)
		map_bh(bh_result, inode->i_sb, phys);
	return 0;
}

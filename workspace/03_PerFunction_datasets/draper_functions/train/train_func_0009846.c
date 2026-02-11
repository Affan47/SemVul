inode_congested(struct inode *inode, int cong_bits)
{


	if (inode && inode_to_wb_is_valid(inode)) {
		struct bdi_writeback *wb;
		bool locked, congested;

		wb = unlocked_inode_to_wb_begin(inode, &locked);
		congested = wb_congested(wb, cong_bits);
		unlocked_inode_to_wb_end(inode, locked);
		return congested;
	}

	return wb_congested(&inode_to_bdi(inode)->wb, cong_bits);
}

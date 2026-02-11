delete_block(struct gfs2_inode *ip, uint64_t block,
		 struct gfs2_buffer_head **bh, const char *btype,
		 void *private)
{
	if (valid_block(ip->i_sbd, block)) {
		fsck_blockmap_set(ip, block, btype, gfs2_block_free);
		return 0;
	}
	return -1;
}

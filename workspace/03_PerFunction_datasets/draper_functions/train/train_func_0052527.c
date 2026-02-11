alloc_metalist(struct gfs2_inode *ip, uint64_t block,
			  struct gfs2_buffer_head **bh, int h, int *is_valid,
			  int *was_duplicate, void *private)
{
	uint8_t q;
	const char *desc = (const char *)private;


	*is_valid = 1;
	*was_duplicate = 0;
	*bh = bread(ip->i_sbd, block);
	q = block_type(block);
	if (blockmap_to_bitmap(q, ip->i_sbd->gfs1) == GFS2_BLKST_FREE) {
		log_debug(_("%s reference to new metadata block "
			    "%lld (0x%llx) is now marked as indirect.\n"),
			  desc, (unsigned long long)block,
			  (unsigned long long)block);
		gfs2_blockmap_set(bl, block, gfs2_indir_blk);
	}
	return meta_is_good;
}

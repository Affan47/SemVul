gfs2_replay_read_block(struct gfs2_inode *ip, unsigned int blk,
			   struct gfs2_buffer_head **bh)
{
	int new = 0;
	uint64_t dblock;
	uint32_t extlen;

	block_map(ip, blk, &new, &dblock, &extlen, FALSE);
	if (!dblock)
		return -EIO;

	*bh = bread(ip->i_sbd, dblock);
	return 0;
}

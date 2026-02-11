get_log_header(struct gfs2_inode *ip, unsigned int blk,
		   struct gfs2_log_header *head)
{
	struct gfs2_buffer_head *bh;
	struct gfs2_log_header lh, *tmp;
	uint32_t hash, saved_hash;
	int error;

	error = gfs2_replay_read_block(ip, blk, &bh);
	if (error)
		return error;

	tmp = (struct gfs2_log_header *)bh->b_data;
	saved_hash = tmp->lh_hash;
	tmp->lh_hash = 0;
	hash = gfs2_disk_hash(bh->b_data, sizeof(struct gfs2_log_header));
	tmp->lh_hash = saved_hash;
	gfs2_log_header_in(&lh, bh);
	brelse(bh);

	if (error || lh.lh_blkno != blk || lh.lh_hash != hash)
		return 1;

	*head = lh;

	return 0;
}

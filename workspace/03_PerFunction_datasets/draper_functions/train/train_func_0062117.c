nilfs_read_log_header(struct the_nilfs *nilfs, sector_t start_blocknr,
		      struct nilfs_segment_summary **sum)
{
	struct buffer_head *bh_sum;

	bh_sum = __bread(nilfs->ns_bdev, start_blocknr, nilfs->ns_blocksize);
	if (bh_sum)
		*sum = (struct nilfs_segment_summary *)bh_sum->b_data;
	return bh_sum;
}

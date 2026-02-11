skip_prev_header(struct scsi_lu *lu)
{
	ssize_t rd;
	struct ssc_info *ssc = dtype_priv(lu);
	struct blk_header_info *h = &ssc->c_blk;

	rd = ssc_read_blkhdr(lu->fd, h, h->prev);
	if (rd)
		return 1;
	if (h->blk_type == BLK_BOT)
		return skip_next_header(lu);
	return 0;
}

jhead_scan(struct gfs2_jdesc *jd, struct gfs2_log_header_host *head)
{
	unsigned int blk = head->lh_blkno;
	struct gfs2_log_header_host lh;
	int error;

	for (;;) {
		if (++blk == jd->jd_blocks)
			blk = 0;

		error = get_log_header(jd, blk, &lh);
		if (error < 0)
			return error;
		if (error == 1)
			continue;

		if (lh.lh_sequence == head->lh_sequence) {
			gfs2_consist_inode(GFS2_I(jd->jd_inode));
			return -EIO;
		}
		if (lh.lh_sequence < head->lh_sequence)
			break;

		*head = lh;
	}

	return 0;
}

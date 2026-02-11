databuf_lo_scan_elements(struct gfs2_jdesc *jd, unsigned int start,
				    struct gfs2_log_descriptor *ld,
				    __be64 *ptr, int pass)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	struct gfs2_glock *gl = ip->i_gl;
	unsigned int blks = be32_to_cpu(ld->ld_data1);
	struct buffer_head *bh_log, *bh_ip;
	u64 blkno;
	u64 esc;
	int error = 0;

	if (pass != 1 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_JDATA)
		return 0;

	gfs2_replay_incr_blk(sdp, &start);
	for (; blks; gfs2_replay_incr_blk(sdp, &start), blks--) {
		blkno = be64_to_cpu(*ptr++);
		esc = be64_to_cpu(*ptr++);

		jd->jd_found_blocks++;

		if (gfs2_revoke_check(jd, blkno, start))
			continue;

		error = gfs2_replay_read_block(jd, start, &bh_log);
		if (error)
			return error;

		bh_ip = gfs2_meta_new(gl, blkno);
		memcpy(bh_ip->b_data, bh_log->b_data, bh_log->b_size);


		if (esc) {
			__be32 *eptr = (__be32 *)bh_ip->b_data;
			*eptr = cpu_to_be32(GFS2_MAGIC);
		}
		mark_buffer_dirty(bh_ip);

		brelse(bh_log);
		brelse(bh_ip);

		jd->jd_replayed_blocks++;
	}

	return error;
}

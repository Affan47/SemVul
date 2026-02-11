revoke_lo_scan_elements(struct gfs2_inode *ip, unsigned int start,
				   struct gfs2_log_descriptor *ld, __be64 *ptr,
				   int pass)
{
	struct gfs2_sbd *sdp = ip->i_sbd;
	unsigned int blks = be32_to_cpu(ld->ld_length);
	unsigned int revokes = be32_to_cpu(ld->ld_data1);
	struct gfs2_buffer_head *bh;
	unsigned int offset;
	uint64_t blkno;
	int first = 1;
	int error;

	if (pass != 0 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_REVOKE)
		return 0;

	offset = sizeof(struct gfs2_log_descriptor);

	for (; blks; gfs2_replay_incr_blk(ip, &start), blks--) {
		error = gfs2_replay_read_block(ip, start, &bh);
		if (error)
			return error;

		if (!first) {
			if (gfs2_check_meta(bh, GFS2_METATYPE_LB))
				continue;
		}
		while (offset + sizeof(uint64_t) <= sdp->sd_sb.sb_bsize) {
			blkno = be64_to_cpu(*(__be64 *)(bh->b_data + offset));
			log_info( _("Journal replay processing revoke for "
				    "block #%lld (0x%llx) for journal+0x%x\n"),
				  (unsigned long long)blkno,
				  (unsigned long long)blkno,
				  start);
			error = gfs2_revoke_add(sdp, blkno, start);
			if (error < 0)
				return error;
			else if (error)
				sd_found_revokes++;

			if (!--revokes)
				break;
			offset += sizeof(uint64_t);
		}

		bmodified(bh);
		brelse(bh);
		offset = sizeof(struct gfs2_meta_header);
		first = 0;
	}
	return 0;
}

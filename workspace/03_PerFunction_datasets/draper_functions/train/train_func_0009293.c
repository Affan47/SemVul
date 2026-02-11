fsck_readi(struct gfs2_inode *ip, void *rbuf, uint64_t roffset,
	       unsigned int size, uint64_t *abs_block)
{
	struct gfs2_sbd *sdp = ip->i_sbd;
	struct gfs2_buffer_head *lbh;
	uint64_t lblock, dblock;
	unsigned int o;
	uint32_t extlen = 0;
	unsigned int amount;
	int not_new = 0;
	int isdir = !!(S_ISDIR(ip->i_di.di_mode));
	int copied = 0;

	*abs_block = 0;
	if (roffset >= ip->i_di.di_size)
		return 0;
	if ((roffset + size) > ip->i_di.di_size)
		size = ip->i_di.di_size - roffset;
	if (!size)
		return 0;
	if (isdir) {
		o = roffset % sdp->sd_jbsize;
		lblock = roffset / sdp->sd_jbsize;
	} else {
		lblock = roffset >> sdp->sd_sb.sb_bsize_shift;
		o = roffset & (sdp->bsize - 1);
	}

	if (!ip->i_di.di_height)
		o += sizeof(struct gfs2_dinode);
	else if (isdir)
		o += sizeof(struct gfs2_meta_header);

	while (copied < size) {
		amount = size - copied;
		if (amount > sdp->bsize - o)
			amount = sdp->bsize - o;
		if (!extlen)
			block_map(ip, lblock, &not_new, &dblock, &extlen,
				  FALSE);
		if (dblock) {
			lbh = bread(sdp, dblock);
			if (*abs_block == 0)
				*abs_block = lbh->b_blocknr;
			dblock++;
			extlen--;
		} else
			lbh = NULL;
		if (lbh) {
			memcpy(rbuf, lbh->b_data + o, amount);
			brelse(lbh);
		} else {
			memset(rbuf, 0, amount);
		}
		copied += amount;
		lblock++;
		o = (isdir) ? sizeof(struct gfs2_meta_header) : 0;
	}
	return copied;
}

fix_metatree(struct gfs2_sbd *sbp, struct gfs2_inode *ip,
		  struct blocklist *blk, uint64_t *first_nonzero_ptr,
		  unsigned int size)
{
	uint64_t block;
	struct gfs2_buffer_head *bh;
	unsigned int amount, ptramt;
	int hdrsize, h, copied = 0, new;
	struct gfs2_meta_header mh;
	char *srcptr = (char *)first_nonzero_ptr;

	mh.mh_magic = GFS2_MAGIC;
	mh.mh_type = GFS2_METATYPE_IN;
	mh.mh_format = GFS2_FORMAT_IN;
	if (!ip->i_di.di_height)
		unstuff_dinode(ip);

	ptramt = blk->mp.mp_list[blk->height] * sizeof(uint64_t);
	amount = size;

	while (copied < size) {
		bh = ip->i_bh;

		for (h = 0; h < blk->height; h++) {
			new = 0;
			lookup_block(ip, bh, h, &blk->mp, 1, &new, &block);
			if (bh != ip->i_bh)
				brelse(bh);
			if (!block)
				break;

			bh = bread(sbp, block);
			if (new)
				memset(bh->b_data, 0, sbp->bsize);
			gfs2_meta_header_out_bh(&mh, bh);
		}

		hdrsize = blk->height ? sizeof(struct gfs2_meta_header) :
			sizeof(struct gfs2_dinode);

		if (amount > sbp->bsize - hdrsize - ptramt)
			amount = sbp->bsize - hdrsize - ptramt;

		memcpy(bh->b_data + hdrsize + ptramt, (char *)srcptr, amount);
		srcptr += amount;
		bmodified(bh);
		if (bh != ip->i_bh)
			brelse(bh);

		copied += amount;

		if (hdrsize + ptramt + amount >= sbp->bsize) {

			blk->mp.mp_list[blk->height] +=
				(amount / sizeof(uint64_t));
			for (h = blk->height; h > 0; h--) {
				if (blk->mp.mp_list[h] >= gfs2_inptrs) {
					blk->mp.mp_list[h] = 0;
					blk->mp.mp_list[h - 1]++;
					continue;
				}
				break;
			}
		}
		amount = size - copied;
		ptramt = 0;
	}
}

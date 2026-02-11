find_rgs_for_bsize(struct gfs2_sbd *sdp, uint64_t startblock,
			      uint32_t *known_bsize)
{
	uint64_t blk, max_rg_size, rb_addr;
	struct gfs2_buffer_head *bh, *rb_bh;
	uint32_t bsize, bsize2;
	uint32_t chk;
	char *p;
	int found_rg;
	struct gfs2_meta_header mh;

	sdp->bsize = GFS2_DEFAULT_BSIZE;
	max_rg_size = 524288;


	for (blk = startblock; blk < startblock + max_rg_size; blk++) {
		bh = bread(sdp, blk);
		found_rg = 0;
		for (bsize = 0; bsize < GFS2_DEFAULT_BSIZE;
		     bsize += GFS2_BASIC_BLOCK) {
			p = bh->b_data + bsize;
			chk = ((struct gfs2_meta_header *)p)->mh_magic;
			if (be32_to_cpu(chk) != GFS2_MAGIC)
				continue;
			chk = ((struct gfs2_meta_header *)p)->mh_type;
			if (be32_to_cpu(chk) == GFS2_METATYPE_RG) {
				found_rg = 1;
				break;
			}
		}
		if (!found_rg)
			continue;

		for (bsize2 = GFS2_BASIC_BLOCK; bsize2 <= GFS2_DEFAULT_BSIZE;
		     bsize2 += GFS2_BASIC_BLOCK) {
			rb_addr = (bh->b_blocknr *
				   (GFS2_DEFAULT_BSIZE / bsize2)) +
				(bsize / bsize2) + 1;
			sdp->bsize = bsize2;
			rb_bh = bread(sdp, rb_addr);
			gfs2_meta_header_in(&mh, rb_bh);
			brelse(rb_bh);
			if (mh.mh_magic == GFS2_MAGIC &&
			    mh.mh_type == GFS2_METATYPE_RB) {
				log_debug(_("boff:%d bsize2:%d rg:0x%llx, "
					    "rb:0x%llx\n"), bsize, bsize2,
					  (unsigned long long)blk,
					  (unsigned long long)rb_addr);
				*known_bsize = bsize2;
				break;
			}
		}
		brelse(bh);
		if (!(*known_bsize)) {
			sdp->bsize = GFS2_DEFAULT_BSIZE;
			continue;
		}

		sdp->bsize = *known_bsize;
		log_warn(_("Block size determined to be: %d\n"), *known_bsize);
		return 0;
	}
	return 0;
}

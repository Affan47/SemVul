pass1_process_rgrp(struct gfs2_sbd *sdp, struct rgrp_tree *rgd)
{
	unsigned k, n, i;
	uint64_t *ibuf = malloc(sdp->bsize * GFS2_NBBY * sizeof(uint64_t));
	int ret;

	for (k = 0; k < rgd->ri.ri_length; k++) {
		n = lgfs2_bm_scan(rgd, k, ibuf, GFS2_BLKST_DINODE);

		if (n) {
			ret = pass1_process_bitmap(sdp, rgd, ibuf, n);
			if (ret)
				return ret;
		}


		if (!sdp->gfs1)
			continue;

		n = lgfs2_bm_scan(rgd, k, ibuf, GFS2_BLKST_UNLINKED);
		for (i = 0; i < n; i++)
			gfs2_blockmap_set(bl, ibuf[i], gfs2_freemeta);
	}

	free(ibuf);
	return 0;
}

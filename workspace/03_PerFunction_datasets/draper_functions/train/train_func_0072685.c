save_allocated(struct rgrp_tree *rgd, struct metafd *mfd)
{
	int blktype;
	unsigned i, j, m;
	uint64_t *ibuf = malloc(sbd.bsize * GFS2_NBBY * sizeof(uint64_t));

	for (i = 0; i < rgd->ri.ri_length; i++) {
		m = lgfs2_bm_scan(rgd, i, ibuf, GFS2_BLKST_DINODE);

		for (j = 0; j < m; j++) {
			block = ibuf[j];
			warm_fuzzy_stuff(block, FALSE);
			blktype = save_block(sbd.device_fd, mfd, block);
			if (blktype == GFS2_METATYPE_DI)
				save_inode_data(mfd);
		}

		if (!sbd.gfs1)
			continue;


		m = lgfs2_bm_scan(rgd, i, ibuf, GFS2_BLKST_UNLINKED);
		for (j = 0; j < m; j++) {
			blktype = save_block(sbd.device_fd, mfd, block);
		}
	}
	free(ibuf);
}

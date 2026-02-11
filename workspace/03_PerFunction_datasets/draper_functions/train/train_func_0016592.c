inode_put(struct gfs2_inode **ip_in)
{
	struct gfs2_inode *ip = *ip_in;
	uint64_t block = ip->i_di.di_num.no_addr;
	struct gfs2_sbd *sdp = ip->i_sbd;

	if (ip->i_bh->b_modified) {
		gfs2_dinode_out(&ip->i_di, ip->i_bh);
		if (!ip->bh_owned && is_system_inode(sdp, block))
			fprintf(stderr, "Warning: Change made to inode "
				"were discarded.\n");


	}
	if (ip->bh_owned)
		brelse(ip->i_bh);
	ip->i_bh = NULL;
	free(ip);
	*ip_in = NULL;
}

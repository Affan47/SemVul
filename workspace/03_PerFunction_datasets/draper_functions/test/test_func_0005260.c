copy_quotas(struct gfs2_sbd *sdp)
{
	struct gfs2_inum inum;
	struct gfs2_inode *oq_ip, *nq_ip;
	int err;

	err = gfs2_lookupi(sdp->master_dir, "quota", 5, &nq_ip);
	if (err) {
		fprintf(stderr, _("Couldn't lookup new quota file: %d\n"), err);
		exit(1);
	}

	gfs2_inum_in(&inum, (char *)&raw_gfs1_ondisk_sb.sb_quota_di);
	oq_ip = lgfs2_inode_read(sdp, inum.no_addr);
	if (oq_ip == NULL) {
		fprintf(stderr, _("Couldn't lookup old quota file: %s\n"), strerror(errno));
		exit(1);
	}

	nq_ip->i_di.di_height = oq_ip->i_di.di_height;
	nq_ip->i_di.di_size = oq_ip->i_di.di_size;
	nq_ip->i_di.di_blocks = oq_ip->i_di.di_blocks;
	memcpy(nq_ip->i_bh->b_data + sizeof(struct gfs2_dinode),
	       oq_ip->i_bh->b_data + sizeof(struct gfs2_dinode),
	       sdp->bsize - sizeof(struct gfs2_dinode));

	oq_ip->i_di.di_height = 0;
	oq_ip->i_di.di_size = 0;

	bmodified(nq_ip->i_bh);
	inode_put(&nq_ip);

	bmodified(oq_ip->i_bh);
	inode_put(&oq_ip);
}

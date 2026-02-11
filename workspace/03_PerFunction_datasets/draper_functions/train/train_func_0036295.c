fsck_system_inode(struct gfs2_sbd *sdp, uint64_t block)
{
	int j;

	if (lf_dip && lf_dip->i_di.di_num.no_addr == block)
		return lf_dip;
	if (!sdp->gfs1)
		return is_system_inode(sdp, block);

	if (sdp->md.statfs && block == sdp->md.statfs->i_di.di_num.no_addr)
		return sdp->md.statfs;
	if (sdp->md.jiinode && block == sdp->md.jiinode->i_di.di_num.no_addr)
		return sdp->md.jiinode;
	if (sdp->md.riinode && block == sdp->md.riinode->i_di.di_num.no_addr)
		return sdp->md.riinode;
	if (sdp->md.qinode && block == sdp->md.qinode->i_di.di_num.no_addr)
		return sdp->md.qinode;
	if (sdp->md.rooti && block == sdp->md.rooti->i_di.di_num.no_addr)
		return sdp->md.rooti;
	for (j = 0; j < sdp->md.journals; j++)
		if (sdp->md.journal && sdp->md.journal[j] &&
		    block == sdp->md.journal[j]->i_di.di_num.no_addr)
			return sdp->md.journal[j];
	return NULL;
}

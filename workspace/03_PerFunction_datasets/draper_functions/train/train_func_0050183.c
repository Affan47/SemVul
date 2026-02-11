rgrp_go_inval(struct gfs2_glock *gl, int flags)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct address_space *mapping = &sdp->sd_aspace;
	struct gfs2_rgrpd *rgd = gl->gl_object;

	if (rgd)
		gfs2_rgrp_brelse(rgd);

	WARN_ON_ONCE(!(flags & DIO_METADATA));
	gfs2_assert_withdraw(sdp, !atomic_read(&gl->gl_ail_count));
	truncate_inode_pages_range(mapping, gl->gl_vm.start, gl->gl_vm.end);

	if (rgd)
		rgd->rd_flags &= ~GFS2_RDF_UPTODATE;
}

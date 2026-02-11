gfs2_bmap_destroy(struct gfs2_sbd *sdp, struct gfs2_bmap *il)
{
	if (il) {
		gfs2_blockmap_destroy(il);
		free(il);
		il = NULL;
	}
	gfs2_special_free(&sdp->eattr_blocks);
	return il;
}

block_show(struct gfs2_sbd *sdp, char *buf)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	ssize_t ret;
	int val = 0;

	if (test_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags))
		val = 1;
	ret = sprintf(buf, "%d\n", val);
	return ret;
}

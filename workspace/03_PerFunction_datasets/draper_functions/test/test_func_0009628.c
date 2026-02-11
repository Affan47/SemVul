drm_gtf2_m(struct edid *edid)
{
	u8 *r = NULL;
	drm_for_each_detailed_block((u8 *)edid, find_gtf2, &r);
	return r ? (r[15] << 8) + r[14] : 0;
}

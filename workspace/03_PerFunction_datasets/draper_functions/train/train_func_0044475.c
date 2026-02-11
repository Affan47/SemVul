gf_rtsp_range_parse(char *range_buf)
{
	GF_RTSPRange *rg;

	if (!strstr(range_buf, "npt")) return NULL;

	GF_SAFEALLOC(rg, GF_RTSPRange);
	if (sscanf(range_buf, "npt=%lf-%lf", &rg->start, &rg->end) != 2) {
		rg->end = -1.0;
		sscanf(range_buf, "npt=%lf-", &rg->start);
	}
	return rg;
}

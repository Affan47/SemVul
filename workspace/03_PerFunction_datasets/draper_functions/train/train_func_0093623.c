gf_dasher_store_segment_info(GF_DASHSegmenterOptions *dash_cfg, const char *SegmentName, Double segStartTime)
{
	char szKey[512];
	if (!dash_cfg->dash_ctx) return GF_OK;

	sprintf(szKey, "%g", segStartTime);
	return gf_cfg_set_key(dash_cfg->dash_ctx, "SegmentsStartTimes", SegmentName, szKey);
}

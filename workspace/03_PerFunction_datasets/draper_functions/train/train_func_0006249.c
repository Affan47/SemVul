gf_odf_size_slc(GF_SLConfig *sl, u32 *outSize)
{
	if (! sl) return GF_BAD_PARAM;

	*outSize = 1;
	if (! sl->predefined)	*outSize += 15;
	if (sl->durationFlag)	*outSize += 8;
	if (! sl->useTimestampsFlag) *outSize += GetTSbytesLen(sl);
	return GF_OK;
}

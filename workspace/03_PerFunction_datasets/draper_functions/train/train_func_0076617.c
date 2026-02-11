gf_odf_size_od_remove(GF_ODRemove *odRem, u32 *outSize)
{
	u32 size;
	if (!odRem) return GF_BAD_PARAM;

	size = 10 * odRem->NbODs;
	*outSize = 0;
	*outSize = size/8;
	if (*outSize * 8 != size) *outSize += 1;
	return GF_OK;
}

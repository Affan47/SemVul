gf_odf_size_descriptor_list(GF_List *descList, u32 *outSize)
{
	GF_Err e;
	GF_Descriptor *tmp;
	u32 tmpSize, count, i;
	if (! descList) return GF_OK;

	count = gf_list_count(descList);
	for ( i = 0; i < count; i++ ) {
		tmp = (GF_Descriptor*)gf_list_get(descList, i);
		if (tmp) {
			e = gf_odf_size_descriptor(tmp, &tmpSize);
			if (e) return e;
			if (tmpSize) *outSize += tmpSize + gf_odf_size_field_size(tmpSize);
		}
	}
	return GF_OK;
}

gf_odf_size_iod(GF_InitialObjectDescriptor *iod, u32 *outSize)
{
	GF_Err e;
	if (! iod) return GF_BAD_PARAM;

	*outSize = 0;
	*outSize += 2;
	if (iod->URLString) {
		*outSize += gf_odf_size_url_string(iod->URLString);
	} else {
		*outSize += 5;
		e = gf_odf_size_descriptor_list(iod->ESDescriptors, outSize);
		if (e) return e;
		e = gf_odf_size_descriptor_list(iod->OCIDescriptors, outSize);
		if (e) return e;
		e = gf_odf_size_descriptor_list(iod->IPMP_Descriptors, outSize);
		if (e) return e;

	}
	e = gf_odf_size_descriptor_list(iod->extensionDescriptors, outSize);
	if (e) return e;
	if (iod->IPMPToolList) {
		u32 tmpSize;
		e = gf_odf_size_descriptor((GF_Descriptor *) iod->IPMPToolList, &tmpSize);
		if (e) return e;
		*outSize += tmpSize + gf_odf_size_field_size(tmpSize);
	}
	return GF_OK;
}

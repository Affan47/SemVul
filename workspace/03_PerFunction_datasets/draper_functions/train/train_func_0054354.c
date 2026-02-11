gf_odf_write_od(GF_BitStream *bs, GF_ObjectDescriptor *od)
{
	GF_Err e;
	u32 size;
	if (! od) return GF_BAD_PARAM;

	e = gf_odf_size_descriptor((GF_Descriptor *)od, &size);
	if (e) return e;
	e = gf_odf_write_base_descriptor(bs, od->tag, size);
	if (e) return e;

	gf_bs_write_int(bs, od->objectDescriptorID, 10);
	gf_bs_write_int(bs, od->URLString != NULL ? 1 : 0, 1);
	gf_bs_write_int(bs, 31, 5);

	if (od->URLString) {
		gf_odf_write_url_string(bs, od->URLString);
	} else {
		e = gf_odf_write_descriptor_list(bs, od->ESDescriptors);
		if (e) return e;
		e = gf_odf_write_descriptor_list(bs, od->OCIDescriptors);
		if (e) return e;
		e = gf_odf_write_descriptor_list_filter(bs, od->IPMP_Descriptors, GF_ODF_IPMP_PTR_TAG);
		if (e) return e;
		e = gf_odf_write_descriptor_list_filter(bs, od->IPMP_Descriptors, GF_ODF_IPMP_TAG);
		if (e) return e;
	}
	e = gf_odf_write_descriptor_list(bs, od->extensionDescriptors);
	return GF_OK;
}

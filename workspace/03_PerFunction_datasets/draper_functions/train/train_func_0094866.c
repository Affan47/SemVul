gf_odf_read_od_update(GF_BitStream *bs, GF_ODUpdate *odUp, u32 gf_odf_size_command)
{
	GF_Descriptor *tmp;
	GF_Err e = GF_OK;
	u32 tmpSize = 0, nbBytes = 0;
	if (! odUp) return GF_BAD_PARAM;

	while (nbBytes < gf_odf_size_command) {
		e = gf_odf_parse_descriptor(bs, &tmp, &tmpSize);
		if (e) return e;
		e = AddToODUpdate(odUp, tmp);
		if (e) return e;
		nbBytes += tmpSize + gf_odf_size_field_size(tmpSize);
	}

	gf_bs_align(bs);
	if (nbBytes != gf_odf_size_command) return GF_ODF_INVALID_COMMAND;
	return e;
}

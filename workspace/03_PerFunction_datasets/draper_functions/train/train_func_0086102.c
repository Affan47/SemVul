gf_odf_read_esd_remove(GF_BitStream *bs, GF_ESDRemove *esdRem, u32 gf_odf_size_command)
{
	u32 i = 0;
	if (! esdRem) return GF_BAD_PARAM;

	esdRem->ODID = gf_bs_read_int(bs, 10);
	gf_bs_read_int(bs, 6);


	if (gf_odf_size_command < 2) return GF_ODF_INVALID_DESCRIPTOR;
	if (gf_odf_size_command == 2) {
		esdRem->NbESDs = 0;
		esdRem->ES_ID = NULL;
		return GF_OK;
	}
	esdRem->NbESDs = (gf_odf_size_command - 2) / 2;
	esdRem->ES_ID = (u16 *) gf_malloc(sizeof(u16) * esdRem->NbESDs);
	if (! esdRem->ES_ID) return GF_OUT_OF_MEM;
	for (i = 0; i < esdRem->NbESDs ; i++) {
		esdRem->ES_ID[i] = gf_bs_read_int(bs, 16);
	}

	gf_bs_align(bs);
	return GF_OK;
}

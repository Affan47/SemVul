gf_odf_read_ipmp_remove(GF_BitStream *bs, GF_IPMPRemove *ipmpRem, u32 gf_odf_size_command)
{
	u32 i;
	if (! ipmpRem) return GF_BAD_PARAM;


	if (!gf_odf_size_command) return GF_OK;

	ipmpRem->NbIPMPDs = gf_odf_size_command;
	ipmpRem->IPMPDescID = (u8 *) gf_malloc(sizeof(u8) * ipmpRem->NbIPMPDs);
	if (! ipmpRem->IPMPDescID) return GF_OUT_OF_MEM;

	for (i = 0; i < ipmpRem->NbIPMPDs; i++) {
		ipmpRem->IPMPDescID[i] = gf_bs_read_int(bs, 8);
	}

	gf_bs_align(bs);
	return GF_OK;
}

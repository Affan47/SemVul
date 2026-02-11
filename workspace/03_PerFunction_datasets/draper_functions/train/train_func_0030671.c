gf_odf_read_base_command(GF_BitStream *bs, GF_BaseODCom *bcRem, u32 gf_odf_size_command)
{
	if (! bcRem) return GF_BAD_PARAM;

	bcRem->dataSize = gf_odf_size_command;
	bcRem->data = (char *) gf_malloc(sizeof(char) * bcRem->dataSize);
	if (! bcRem->data) return GF_OUT_OF_MEM;
	gf_bs_read_data(bs, bcRem->data, bcRem->dataSize);
	return GF_OK;
}

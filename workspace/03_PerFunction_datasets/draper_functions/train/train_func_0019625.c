gf_odf_read_od_remove(GF_BitStream *bs, GF_ODRemove *odRem, u32 gf_odf_size_command)
{
	u32 i = 0, nbBits;
	if (! odRem) return GF_BAD_PARAM;

	odRem->NbODs = (u32 ) (gf_odf_size_command * 8) / 10;
	odRem->OD_ID = (u16 *) gf_malloc(sizeof(u16) * odRem->NbODs);
	if (! odRem->OD_ID) return GF_OUT_OF_MEM;

	for (i = 0; i < odRem->NbODs ; i++) {
		odRem->OD_ID[i] = gf_bs_read_int(bs, 10);
	}
	nbBits = odRem->NbODs * 10;

	nbBits += gf_bs_align(bs);
	if (nbBits != (gf_odf_size_command * 8)) return GF_ODF_INVALID_COMMAND;
	return GF_OK;
}

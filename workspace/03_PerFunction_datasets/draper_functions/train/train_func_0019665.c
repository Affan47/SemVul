Write_ImmediateDTE(GF_ImmediateDTE *dte, GF_BitStream *bs)
{
	char data[14];
	gf_bs_write_u8(bs, dte->source);
	gf_bs_write_u8(bs, dte->dataLength);
	gf_bs_write_data(bs, dte->data, dte->dataLength);
	if (dte->dataLength < 14) {
		memset(data, 0, 14);
		gf_bs_write_data(bs, data, 14 - dte->dataLength);
	}
	return GF_OK;
}

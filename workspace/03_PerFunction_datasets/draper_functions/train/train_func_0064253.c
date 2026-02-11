piff_tenc_Read(GF_Box *s, GF_BitStream *bs)
{
	GF_PIFFTrackEncryptionBox *ptr = (GF_PIFFTrackEncryptionBox*)s;

	if (ptr->size<4) return GF_ISOM_INVALID_FILE;
	ptr->version = gf_bs_read_u8(bs);
	ptr->flags = gf_bs_read_u24(bs);
	ptr->size -= 4;

	ptr->AlgorithmID = gf_bs_read_int(bs, 24);
	ptr->IV_size = gf_bs_read_u8(bs);
	gf_bs_read_data(bs, ptr->KID, 16);
	ptr->size -= 20;
	return GF_OK;
}

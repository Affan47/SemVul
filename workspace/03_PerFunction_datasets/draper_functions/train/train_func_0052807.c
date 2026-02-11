piff_pssh_Read(GF_Box *s, GF_BitStream *bs)
{
	GF_PIFFProtectionSystemHeaderBox *ptr = (GF_PIFFProtectionSystemHeaderBox*)s;

	if (ptr->size<4) return GF_ISOM_INVALID_FILE;
	ptr->version = gf_bs_read_u8(bs);
	ptr->flags = gf_bs_read_u24(bs);
	ptr->size -= 4;

	gf_bs_read_data(bs, ptr->SystemID, 16);
	ptr->private_data_size = gf_bs_read_u32(bs);
	ptr->size -= 20;
	ptr->private_data = gf_malloc(sizeof(char)*ptr->private_data_size);
	gf_bs_read_data(bs, ptr->private_data, ptr->private_data_size);
	ptr->size -= ptr->private_data_size;
	return GF_OK;
}

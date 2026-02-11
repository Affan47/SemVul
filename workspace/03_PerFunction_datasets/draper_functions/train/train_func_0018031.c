egdi_in_offset(const struct egdich* ch, int ind)
{
	int chind, offset = 0;

	for (chind=0; chind<ind; chind++)
		offset += egd_get_data_size(ch[chind].dtype);

	return offset;
}

dime_fill_record_header(const struct dime_record *record,
	char *data, size_t size, uint flags)
{
	unsigned char value;

	g_assert(record);
	g_assert(data);
	g_assert(size >= DIME_HEADER_SIZE);

	value = DIME_VERSION << 3;
	value |= (DIME_F_MB & flags);
	value |= (DIME_F_ME & flags);
	value |= (DIME_F_CF & flags);

	poke_u8(&data[0], value);
	poke_u8(&data[1], (record->type_t << 4) | record->resrvd);
	poke_be16(&data[2], record->options_length);
	poke_be16(&data[4], record->id_length);
	poke_be16(&data[6], record->type_length);
	poke_be32(&data[8], record->data_length);
}

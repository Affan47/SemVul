dime_create_record(const struct dime_record *record,
	char **data_ptr, bool first, bool last)
{
	size_t size;

	size = DIME_HEADER_SIZE +
		dime_ceil(record->options_length) +
		dime_ceil(record->id_length) +
		dime_ceil(record->type_length) +
		dime_ceil(record->data_length);

	if (data_ptr) {
		char *data0, *data;
		uint flags;

		data0 = g_malloc(size);
		data = data0;

		flags = (first ? DIME_F_MB : 0) | (last ?  DIME_F_ME : 0);
		dime_fill_record_header(record, data, size, flags);
		data += DIME_HEADER_SIZE;

		data += copy_and_pad(data, record->options, record->options_length);
		data += copy_and_pad(data, record->id, record->id_length);
		data += copy_and_pad(data, record->type, record->type_length);
		data += copy_and_pad(data, record->data, record->data_length);

		*data_ptr = data0;
	}
	return size;
}

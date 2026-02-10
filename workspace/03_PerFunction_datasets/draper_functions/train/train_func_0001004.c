pstore_table_import_columns(struct pstore_table *self, const char *filename)
{
	FILE *input;
	struct fields_reader *reader;
	struct fields_record *record;
	unsigned long ndx;

	input = fopen(filename, "r");
	if (input == NULL)
		die("fopen: %s", strerror(errno));

	reader = fields_read_file(input, &dsv_iterator_format, &fields_defaults);
	if (reader == NULL)
		die("fields_read_file");

	record = fields_record_alloc(&fields_defaults);
	if (record == NULL)
		die("fields_record_alloc");

	if (fields_reader_read(reader, record) != 0)
		die("fields_reader_read");

	for (ndx = 0; ndx < fields_record_size(record); ndx++) {
		struct fields_field	field;
		struct pstore_column	*column;

		if (fields_record_field(record, ndx, &field) != 0)
			die("fields_record_field");

		column = pstore_column_new(field.value, ndx, VALUE_TYPE_STRING);
		if (column == NULL)
			die("pstore_column_new");

		if (pstore_table_add(self, column) < 0)
			die("pstore_table_add");
	}

	fields_record_free(record);

	fields_reader_free(reader);

	fclose(input);
}

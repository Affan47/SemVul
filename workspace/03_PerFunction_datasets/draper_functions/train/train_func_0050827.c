pstore_table_write(struct pstore_table *self, int fd)
{
	struct pstore_file_table f_table;
	off_t start_off, end_off;
	unsigned long ndx;
	uint64_t size;

	start_off = lseek(fd, sizeof(f_table), SEEK_CUR);
	if (start_off < 0)
		return -1;

	for (ndx = 0; ndx < self->nr_columns; ndx++) {
		struct pstore_column *column = self->columns[ndx];

		if (pstore_column_write(column, fd) < 0)
			return -1;
	}

	end_off = lseek(fd, 0, SEEK_CUR);
	if (end_off < 0)
		return -1;

	size = end_off - start_off;

	if (lseek(fd, -(sizeof(f_table) + size), SEEK_CUR) < 0)
		return -1;

	f_table = (struct pstore_file_table) {
		.table_id	= self->table_id,

		.c_index	= (struct pstore_file_column_idx) {
			.nr_columns	= self->nr_columns,
			.c_index_next	= PSTORE_END_OF_CHAIN,
		},
	};
	strncpy(f_table.name, self->name, PSTORE_TABLE_NAME_LEN);

	if (write_in_full(fd, &f_table, sizeof(f_table)) != sizeof(f_table))
		return -1;

	if (lseek(fd, size, SEEK_CUR) < 0)
		return -1;

	return 0;
}

pstore_column_write(struct pstore_column *self, int fd)
{
	struct pstore_file_column f_column;

	f_column = (struct pstore_file_column) {
		.column_id	= self->column_id,
		.type		= self->type,
		.first_extent	= self->first_extent,
		.last_extent	= self->last_extent,
	};
	strncpy(f_column.name, self->name, PSTORE_COLUMN_NAME_LEN);

	if (write_in_full(fd, &f_column, sizeof(f_column)) != sizeof(f_column))
		return -1;

	return 0;
}

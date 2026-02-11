pstore_table_stat(struct pstore_table *self, int fd)
{
	unsigned long ndx;

	printf("# table '%s'\n", self->name);

	for (ndx = 0; ndx < self->nr_columns; ndx++) {
		struct pstore_column *column = self->columns[ndx];

		pstore_column_stat(column, fd);
	}
}

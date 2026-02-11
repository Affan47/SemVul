export(struct pstore_table *table, int input, int output)
{
	struct pstore_table_iterator_state state;
	unsigned long ndx;

	for (ndx = 0; ndx < table->nr_columns; ndx++) {
		struct pstore_column *column = table->columns[ndx];

		write_or_die(output, column->name, strlen(column->name));
		if (ndx == table->nr_columns - 1)
			write_or_die(output, "\n", 1);
		else
			write_or_die(output, ",", 1);
	}

	state = (struct pstore_table_iterator_state) {
		.fd		= input,
		.table		= table,
	};

	pstore_table_export_values(table, &pstore_table_iterator, &state, output);
}

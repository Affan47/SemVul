write_row_data(fitstable_t* table, void* data, int R) {
	assert(table);
	assert(data);
	if (in_memory(table)) {
		ensure_row_list_exists(table);
		bl_append(table->rows, data);

		table->table->nr++;
		return 0;
	}
	if (R == 0)
		R = fitstable_row_size(table);
	if (fwrite(data, 1, R, table->fid) != R) {
		SYSERROR("Failed to write a row to %s", table->fn);
		return -1;
	}
	assert(table->table);
    table->table->nr++;
	return 0;
}

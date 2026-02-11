_destroy_row_data(struct part_row_data *row, uint16_t num_rows) {
	uint16_t i;
	for (i = 0; i < num_rows; i++) {
		FREE_NULL_BITMAP(row[i].row_bitmap);
		if (row[i].job_list) {
			uint32_t j;
			for (j = 0; j < row[i].num_jobs; j++)
				row[i].job_list[j] = NULL;
			xfree(row[i].job_list);
		}
	}
	xfree(row);
}

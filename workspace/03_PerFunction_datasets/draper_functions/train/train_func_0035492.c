cr_sort_part_rows(struct part_res_record *p_ptr)
{
	uint32_t i, j, a, b;

	if (!p_ptr->row)
		return;

	for (i = 0; i < p_ptr->num_rows; i++) {
		if (p_ptr->row[i].row_bitmap)
			a = bit_set_count(p_ptr->row[i].row_bitmap);
		else
			a = 0;
		for (j = i+1; j < p_ptr->num_rows; j++) {
			if (!p_ptr->row[j].row_bitmap)
				continue;
			b = bit_set_count(p_ptr->row[j].row_bitmap);
			if (b > a) {
				_swap_rows(&(p_ptr->row[i]), &(p_ptr->row[j]));
			}
		}
	}
	return;
}

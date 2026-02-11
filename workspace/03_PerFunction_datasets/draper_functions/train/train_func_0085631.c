update_index2(struct isl_tab_var *var,
	unsigned row1, unsigned col1,
	unsigned r1, unsigned r2, unsigned d1, unsigned d2)
{
	if (var->index == -1)
		return;
	if (var->is_row) {
		if (var->index < r2)
			var->index += r1;
		else
			var->index += row1;
	} else {
		if (var->index < d2)
			var->index += d1;
		else
			var->index += col1;
	}
}

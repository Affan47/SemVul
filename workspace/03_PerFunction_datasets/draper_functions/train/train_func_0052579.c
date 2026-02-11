needs_invert(__isl_keep isl_mat *div, int row)
{
	int i;
	int cmp;

	for (i = div->n_col - 1; i >= 1; --i) {
		if (isl_int_is_zero(div->row[row][i]))
			continue;
		isl_int_mul_ui(div->row[row][i], div->row[row][i], 2);
		cmp = isl_int_cmp(div->row[row][i], div->row[row][0]);
		isl_int_divexact_ui(div->row[row][i], div->row[row][i], 2);
		if (cmp)
			return cmp > 0;
		if (i == 1)
			return 1;
	}

	return 0;
}

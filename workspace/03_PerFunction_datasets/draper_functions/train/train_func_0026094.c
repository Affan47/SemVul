last_var_col_or_int_par_col(struct isl_tab *tab, int row)
{
	unsigned off = 2 + tab->M;
	int i;

	for (i = tab->n_var - tab->n_div - 1; i >= 0 && i >= tab->n_param; --i) {
		int col;
		if (tab->var[i].is_row)
			continue;
		col = tab->var[i].index;
		if (col <= tab->n_dead)
			continue;
		if (!isl_int_is_zero(tab->mat->row[row][off + col]))
			return col;
	}
	for (i = tab->n_dead; i < tab->n_col; ++i) {
		if (isl_int_is_one(tab->mat->row[row][off + i]))
			return i;
		if (isl_int_is_negone(tab->mat->row[row][off + i]))
			return i;
	}
	return -1;
}

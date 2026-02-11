sign_of_min(struct isl_tab *tab, struct isl_tab_var *var)
{
	int row, col;
	struct isl_tab_var *pivot_var = NULL;

	if (min_is_manifestly_unbounded(tab, var))
		return -1;
	if (!var->is_row) {
		col = var->index;
		row = pivot_row(tab, NULL, -1, col);
		pivot_var = var_from_col(tab, col);
		if (isl_tab_pivot(tab, row, col) < 0)
			return -2;
		if (var->is_redundant)
			return 0;
		if (isl_int_is_neg(tab->mat->row[var->index][1])) {
			if (var->is_nonneg) {
				if (!pivot_var->is_redundant &&
				    pivot_var->index == row) {
					if (isl_tab_pivot(tab, row, col) < 0)
						return -2;
				} else
					if (restore_row(tab, var) < -1)
						return -2;
			}
			return -1;
		}
	}
	if (var->is_redundant)
		return 0;
	while (!isl_int_is_neg(tab->mat->row[var->index][1])) {
		find_pivot(tab, var, var, -1, &row, &col);
		if (row == var->index)
			return -1;
		if (row == -1)
			return isl_int_sgn(tab->mat->row[var->index][1]);
		pivot_var = var_from_col(tab, col);
		if (isl_tab_pivot(tab, row, col) < 0)
			return -2;
		if (var->is_redundant)
			return 0;
	}
	if (pivot_var && var->is_nonneg) {

		if (!pivot_var->is_redundant && pivot_var->index == row) {
			if (isl_tab_pivot(tab, row, col) < 0)
				return -2;
		} else
			if (restore_row(tab, var) < -1)
				return -2;
	}
	return -1;
}

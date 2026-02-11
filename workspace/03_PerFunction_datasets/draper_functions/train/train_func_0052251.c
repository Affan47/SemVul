isl_tab_min_at_most_neg_one(struct isl_tab *tab, struct isl_tab_var *var)
{
	int row, col;
	struct isl_tab_var *pivot_var;

	if (min_is_manifestly_unbounded(tab, var))
		return 1;
	if (!var->is_row) {
		col = var->index;
		row = pivot_row(tab, NULL, -1, col);
		pivot_var = var_from_col(tab, col);
		if (isl_tab_pivot(tab, row, col) < 0)
			return -1;
		if (var->is_redundant)
			return 0;
		if (row_at_most_neg_one(tab, var->index)) {
			if (var->is_nonneg) {
				if (!pivot_var->is_redundant &&
				    pivot_var->index == row) {
					if (isl_tab_pivot(tab, row, col) < 0)
						return -1;
				} else
					if (restore_row(tab, var) < -1)
						return -1;
			}
			return 1;
		}
	}
	if (var->is_redundant)
		return 0;
	do {
		find_pivot(tab, var, var, -1, &row, &col);
		if (row == var->index) {
			if (restore_row(tab, var) < -1)
				return -1;
			return 1;
		}
		if (row == -1)
			return 0;
		pivot_var = var_from_col(tab, col);
		if (isl_tab_pivot(tab, row, col) < 0)
			return -1;
		if (var->is_redundant)
			return 0;
	} while (!row_at_most_neg_one(tab, var->index));
	if (var->is_nonneg) {

		if (!pivot_var->is_redundant && pivot_var->index == row)
			if (isl_tab_pivot(tab, row, col) < 0)
				return -1;
		if (restore_row(tab, var) < -1)
			return -1;
	}
	return 1;
}

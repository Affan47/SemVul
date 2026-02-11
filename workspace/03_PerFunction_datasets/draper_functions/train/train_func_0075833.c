isl_tab_cone_is_bounded(struct isl_tab *tab)
{
	int i;

	if (!tab)
		return -1;
	if (tab->empty)
		return 1;
	if (tab->n_dead == tab->n_col)
		return 1;

	for (;;) {
		for (i = tab->n_redundant; i < tab->n_row; ++i) {
			struct isl_tab_var *var;
			int sgn;
			var = isl_tab_var_from_row(tab, i);
			if (!var->is_nonneg)
				continue;
			sgn = sign_of_max(tab, var);
			if (sgn < -1)
				return -1;
			if (sgn != 0)
				return 0;
			if (close_row(tab, var) < 0)
				return -1;
			break;
		}
		if (tab->n_dead == tab->n_col)
			return 1;
		if (i == tab->n_row)
			return 0;
	}
}

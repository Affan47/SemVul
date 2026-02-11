con_is_redundant(struct isl_tab *tab, struct isl_tab_var *var)
{
	if (!tab)
		return -1;
	if (tab->rational) {
		int sgn = sign_of_min(tab, var);
		if (sgn < -1)
			return -1;
		return sgn >= 0;
	} else {
		int irred = isl_tab_min_at_most_neg_one(tab, var);
		if (irred < 0)
			return -1;
		return !irred;
	}
}

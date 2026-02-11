may_be_equality(struct isl_tab *tab, int row)
{
	return tab->rational ? isl_int_is_zero(tab->mat->row[row][1])
			     : isl_int_lt(tab->mat->row[row][1],
					    tab->mat->row[row][0]);
}

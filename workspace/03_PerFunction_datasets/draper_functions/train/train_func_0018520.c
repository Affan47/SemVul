e_table_header_get_selected (ETableHeader *eth)
{
	gint i;
	gint selected = 0;

	g_return_val_if_fail (eth != NULL, 0);
	g_return_val_if_fail (E_IS_TABLE_HEADER (eth), 0);

	for (i = 0; i < eth->col_count; i++) {
		if (eth->columns[i]->selected)
			selected++;
	}

	return selected;
}

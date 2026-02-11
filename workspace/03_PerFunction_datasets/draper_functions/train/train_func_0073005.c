table_sorter_get_model_to_sorted_array (ESorter *sorter,
                                        gint **array,
                                        gint *count)
{
	ETableSorter *table_sorter = E_TABLE_SORTER (sorter);

	if (array || count) {
		table_sorter_backsort (table_sorter);

		if (array)
			*array = table_sorter->backsorted;
		if (count)
			*count = e_table_model_row_count(table_sorter->source);
	}
}

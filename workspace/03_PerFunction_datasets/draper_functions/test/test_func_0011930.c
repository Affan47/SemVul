e_table_view_to_model_row (ETable *e_table,
                           gint view_row)
{
	g_return_val_if_fail (E_IS_TABLE (e_table), -1);

	if (e_table->sorter)
		return e_sorter_sorted_to_model (E_SORTER (e_table->sorter), view_row);
	else
		return view_row;
}

e_table_selected_count (ETable *e_table)
{
	g_return_val_if_fail (E_IS_TABLE (e_table), -1);

	return e_selection_model_selected_count (E_SELECTION_MODEL (e_table->selection));
}

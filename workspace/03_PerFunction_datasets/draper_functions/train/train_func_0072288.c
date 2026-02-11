et_table_rows_deleted (ETableModel *table_model,
                       gint row,
                       gint count,
                       ETable *et)
{
	gint row_count = e_table_model_row_count (table_model);
	if (!et->need_rebuild) {
		gint i;
		for (i = 0; i < count; i++)
			e_table_group_remove (et->group, row + i);
		if (row != row_count)
			e_table_group_decrement (et->group, row, count);
		CHECK_HORIZONTAL (et);
	}
}

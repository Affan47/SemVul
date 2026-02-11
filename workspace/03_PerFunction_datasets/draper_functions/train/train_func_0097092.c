e_table_item_get_focused_column (ETableItem *eti)
{
	gint cursor_col;

	g_return_val_if_fail (eti != NULL, -1);
	g_return_val_if_fail (E_IS_TABLE_ITEM (eti), -1);

	g_object_get (
		eti->selection,
		"cursor_col", &cursor_col,
		NULL);

	return cursor_col;
}

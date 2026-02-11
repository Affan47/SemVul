nemo_column_chooser_set_settings (NemoColumnChooser *chooser,
				      char **visible_columns,
				      char **column_order)
{
	g_return_if_fail (NEMO_IS_COLUMN_CHOOSER (chooser));
	g_return_if_fail (visible_columns != NULL);
	g_return_if_fail (column_order != NULL);

	set_visible_columns (chooser, visible_columns);
	set_column_order (chooser, column_order);

	list_changed (chooser);
}

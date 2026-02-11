abi_table_resize(AbiTable* table)
{
	guint width;
	guint height;
	char* text;
	GtkRequisition size;

	UT_return_if_fail(table);

	if (table->selected_rows == 0 && table->selected_cols == 0)
		text = g_strdup(table->szCancel);
	else
	{
		UT_UTF8String prText =  "%d x %d ";
		UT_UTF8String s = table->szTable;
		prText += s;
		text = g_strdup_printf(prText.utf8_str(), table->selected_rows, table->selected_cols);
	}
	cells_to_pixels(table->total_cols, table->total_rows, &width, &height);
	gtk_widget_get_preferred_size(GTK_WIDGET(table->window_label), &size, NULL);

	gtk_label_set_text(table->window_label, text);
	gtk_window_resize(table->window, width + 1, height + size.height);

	g_free(text);
}

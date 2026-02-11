on_filter_activate(GtkEntry *entry, gpointer user_data)
{


	filter = g_strsplit_set(gtk_entry_get_text(entry), "; ", -1);
	if (filter == NULL || g_strv_length(filter) == 0)
	{
		clear_filter();
	}
	ui_combo_box_add_to_history(GTK_COMBO_BOX_ENTRY(filter_combo), NULL, 0);
	refresh();
}

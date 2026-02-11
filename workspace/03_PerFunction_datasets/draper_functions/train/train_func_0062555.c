on_selection_changed (GtkTreeSelection *treeselection,
		      gpointer user_data)
{
	NemoBookmark *selected;
	const char *name = NULL;
	char *entry_text = NULL;
	GFile *location;

	g_assert (GTK_IS_ENTRY (name_field));
	g_assert (GTK_IS_ENTRY (uri_field));

	selected = get_selected_bookmark ();

	if (selected) {
		name = nemo_bookmark_get_name (selected);
		location = nemo_bookmark_get_location (selected);
		entry_text = g_file_get_parse_name (location);

		g_object_unref (location);
	}


	gtk_widget_set_sensitive (remove_button, selected != NULL);
        gtk_widget_set_sensitive (jump_button, selected != NULL);
	gtk_widget_set_sensitive (name_field, selected != NULL);
	gtk_widget_set_sensitive (uri_field, selected != NULL);

	g_signal_handler_block (name_field, name_field_changed_signal_id);
	nemo_entry_set_text (NEMO_ENTRY (name_field),
				 name ? name : "");
	g_signal_handler_unblock (name_field, name_field_changed_signal_id);

	g_signal_handler_block (uri_field, uri_field_changed_signal_id);
	nemo_entry_set_text (NEMO_ENTRY (uri_field),
				 entry_text ? entry_text : "");
	g_signal_handler_unblock (uri_field, uri_field_changed_signal_id);

	text_changed = FALSE;
	name_text_changed = FALSE;

	g_free (entry_text);
}

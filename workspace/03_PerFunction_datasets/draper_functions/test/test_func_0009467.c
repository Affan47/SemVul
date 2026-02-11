on_key_name_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
	KTKey *other_key;
	char *entry_text;

	if (selected_key)
	{
		entry_text = (char*) gtk_entry_get_text (GTK_ENTRY(editable));

		other_key = KTKeyList_find_key (&key_list, entry_text);

		if (other_key == NULL || other_key == selected_key)
		{

			KTKey_set_name (selected_key, entry_text);
			reload_key_treeview (&key_list, GTK_WIDGET(editable));
			file_modified = TRUE;
		}
	}
}

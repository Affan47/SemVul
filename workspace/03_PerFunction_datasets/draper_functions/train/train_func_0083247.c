post_insert_update (ENameSelectorEntry *name_selector_entry,
                    gint position)
{
	const gchar *text;
	glong length;

	text = gtk_entry_get_text (GTK_ENTRY (name_selector_entry));
	length = g_utf8_strlen (text, -1);
	text = g_utf8_next_char (text);

	if (*text == '\0') {

		insert_destination_at_position (name_selector_entry, 0);
	} else {

		modify_destination_at_position (name_selector_entry, position);
	}


	if (position < length)
		generate_attribute_list (name_selector_entry);
}

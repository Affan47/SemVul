nemo_entry_insert_text (GtkEditable *editable, const gchar *text,
			    int length, int *position)
{
	NemoEntry *entry;

	entry = NEMO_ENTRY(editable);


	if (entry->details->user_edit) {
		g_signal_emit (editable, signals[USER_CHANGED], 0);
	}

	parent_editable_interface->insert_text (editable, text, length, position);

	g_signal_emit (editable, signals[SELECTION_CHANGED], 0);
}

primary_get_cb(GtkClipboard *clipboard,
						   GtkSelectionData *data, guint info,
						   gpointer user_data) {
	GtkHex *gh = GTK_HEX(user_data);
	if(gh->selection.start != gh->selection.end) {
		gint start_pos;
		gint end_pos;
		guchar *text;

		start_pos = MIN(gh->selection.start, gh->selection.end);
		end_pos = MAX(gh->selection.start, gh->selection.end);

		text = hex_document_get_data(gh->document, start_pos,
									 end_pos - start_pos);
		gtk_selection_data_set_text(data, text, end_pos - start_pos);
		g_free(text);
	}
}

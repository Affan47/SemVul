gtk_hex_real_paste_from_clipboard(GtkHex *gh)
{
	GtkHexClass *klass = GTK_HEX_CLASS(GTK_WIDGET_GET_CLASS(gh));
	gchar *text;

	text = gtk_clipboard_wait_for_text(klass->clipboard);
	if(text) {
		hex_document_set_data(gh->document, gh->cursor_pos,
							  strlen(text), 0, text, TRUE);
		gtk_hex_set_cursor(gh, gh->cursor_pos + strlen(text));
		g_free(text);
	}
}

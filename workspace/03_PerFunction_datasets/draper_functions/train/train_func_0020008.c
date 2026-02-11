replace_next_cb(GtkButton *button, gpointer unused)
{
	GtkHex *gh;
	guint offset, str_len;
	gchar *str = NULL;
	GHexWindow *win = ghex_window_get_active();

	if(win == NULL || win->gh == NULL) {
		display_error_dialog (win, _("There is no active document to search!"));
		return;
	}

	gh = win->gh;

	if((str_len = get_search_string(replace_dialog->f_doc, &str)) == 0) {
		display_error_dialog (win, _("There is no string to search for!"));
		return;
	}

	if(hex_document_find_forward(gh->document,
								 gh->cursor_pos+1, str, str_len, &offset))
		gtk_hex_set_cursor(gh, offset);
	else {
		display_info_dialog(win, _("String was not found!\n"));
		ghex_window_flash(win, _("End Of File reached"));
	}

	if(NULL != str)
		g_free(str);
}

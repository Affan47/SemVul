find_delete_event_cb(GtkWidget *w, GdkEventAny *e, FindDialog *dialog)
{
	GHexWindow *win = ghex_window_get_active();
	GtkHex *gh = win->gh;

	if (dialog->auto_highlight) gtk_hex_delete_autohighlight(gh, dialog->auto_highlight);
	dialog->auto_highlight = NULL;
	gtk_widget_hide(w);

	return TRUE;
}

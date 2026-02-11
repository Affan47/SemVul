settings_window_close(GtkWidget *window, GtkWidget *button)
{
	START_FUNC
	static gboolean closed=FALSE;
	if (closed) return;
	closed=TRUE;
	if (settings_dirty()) {
		if (GTK_RESPONSE_ACCEPT==tools_dialog(_("Confirm"), GTK_WINDOW(window),
			GTK_STOCK_APPLY, GTK_STOCK_DISCARD, _("Discard changes?")))
			settings_window_commit(NULL, NULL);
		else settings_window_rollback(NULL, NULL);
	}
	if (settings_window->notify_id>0) settings_unregister(settings_window->notify_id);
	settings_window->notify_id=0;

	if (settings_window->style_list) g_object_unref(G_OBJECT(settings_window->style_list));
	settings_window->style_list=NULL;
	if (window) gtk_widget_destroy(GTK_WIDGET(window));
	if (settings_window->gtk_exit) exit(0);
	closed=FALSE;
	END_FUNC
}

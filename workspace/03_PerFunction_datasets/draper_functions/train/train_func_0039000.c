ay_chat_window_updated(chat_window *cw, const char *message)
{
	GdkColor color;
	GtkWidget *notebook = NULL, *child = NULL, *label = NULL;
	int curpagenum = -1, winpagenum = -1;

	if (!cw)
		return;

	notebook = cw->notebook;
	child = cw->pane;

	if (notebook) {
		winpagenum = gtk_notebook_page_num(
			GTK_NOTEBOOK(notebook),
			child);
		curpagenum = gtk_notebook_get_current_page(
			GTK_NOTEBOOK(notebook));
	}


	if (ay_chat_window_raise(cw, message))
		return;

	eb_debug(DBG_CORE, "Setting tab to red\n");


	if (!gtk_window_is_active(GTK_WINDOW(cw->window)))
		gtk_window_set_urgency_hint(GTK_WINDOW(cw->window), TRUE);


	if (!notebook || winpagenum == curpagenum)
		return;

	label = ay_chat_get_tab_label(GTK_NOTEBOOK(notebook), child);

	gdk_color_parse("red", &color);
	gtk_widget_modify_fg(label, GTK_STATE_ACTIVE, &color);
}

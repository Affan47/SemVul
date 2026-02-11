evt_cursor_changed(GtkWidget *wid, gpointer user)
{
	CDlg		*cdlg = user;
	GtkTreePath	*path;
	GtkTreeIter	iter;
	gchar		*text = NULL;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(wid), &path, NULL);
	if(path == NULL)
		return;
	gtk_tree_model_get_iter(GTK_TREE_MODEL(cdlg->store), &iter, path);
	if(gtk_tree_model_iter_n_children(GTK_TREE_MODEL(cdlg->store), &iter) != 0)
		return;
	gtk_tree_model_get(GTK_TREE_MODEL(cdlg->store), &iter, 0, &text, -1);
	if(text != NULL)
	{
		g_signal_handler_block(G_OBJECT(cdlg->entry), cdlg->evt_changed);
		gtk_entry_set_text(GTK_ENTRY(cdlg->entry), text);
		gtk_widget_grab_focus(cdlg->entry);
		g_signal_handler_unblock(G_OBJECT(cdlg->entry), cdlg->evt_changed);
		g_string_assign(cdlg->cmd, text);
		g_free(text);
	}
}

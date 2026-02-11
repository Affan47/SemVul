prefs_actions_cancel(GtkWidget *w, gpointer data)
{
	GtkListStore *store;

	if (modified && alertpanel(_("Entry not saved"),
				 _("The entry was not saved. Close anyway?"),
				 GTK_STOCK_CLOSE, _("+_Continue editing"),
				 NULL) != G_ALERTDEFAULT) {
		return;
	} else if (modified_list && alertpanel(_("Actions list not saved"),
				 _("The actions list has been modified. Close anyway?"),
				 GTK_STOCK_CLOSE, _("+_Continue editing"),
				 NULL) != G_ALERTDEFAULT) {
		return;
	}
	modified = FALSE;
	modified_list = FALSE;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW
				(actions.actions_list_view)));
	gtk_list_store_clear(store);
	prefs_actions_read_config();
	gtk_widget_hide(actions.window);
	gtk_window_set_modal(GTK_WINDOW(actions.window), FALSE);
	inc_unlock();
}

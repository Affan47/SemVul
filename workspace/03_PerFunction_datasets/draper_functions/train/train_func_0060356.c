prefs_actions_ok(GtkWidget *widget, gpointer data)
{
	MainWindow *mainwin = (MainWindow *) data;
	GList *list;
	GList *iter;
	MessageView *msgview;
	Compose *compose;
	GtkListStore *store;

	if (modified && alertpanel(_("Entry not saved"),
				 _("The entry was not saved. Close anyway?"),
				 GTK_STOCK_CLOSE, _("+_Continue editing"),
				 NULL) != G_ALERTDEFAULT) {
		return;
	}
	modified = FALSE;
	modified_list = FALSE;
	prefs_actions_set_list();
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW
				(actions.actions_list_view)));
	gtk_list_store_clear(store);
	prefs_actions_write_config();


	main_window_update_actions_menu(mainwin);


	list = messageview_get_msgview_list();
	for (iter = list; iter; iter = iter->next) {
		msgview = (MessageView *) iter->data;
		messageview_update_actions_menu(msgview);
	}


	list = compose_get_compose_list();
	for (iter = list; iter; iter = iter->next) {
		compose = (Compose *) iter->data;
		compose_update_actions_menu(compose);
	}


	prefs_toolbar_update_action_btns();

	gtk_widget_hide(actions.window);
	gtk_window_set_modal(GTK_WINDOW(actions.window), FALSE);
	inc_unlock();
}

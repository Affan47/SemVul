prefs_actions_delete_all_cb(gpointer gtk_action, gpointer data)
{
	GtkListStore *list_store;

	if (alertpanel(_("Delete all actions"),
			  _("Do you really want to delete all the actions?"),
			  GTK_STOCK_CANCEL, GTK_STOCK_DELETE, NULL) != G_ALERTDEFAULT)
	   return;

	list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(actions.actions_list_view)));
	prefs_actions_clear_list(list_store);
	modified = FALSE;

	prefs_actions_reset_dialog();
	modified_list = TRUE;
}

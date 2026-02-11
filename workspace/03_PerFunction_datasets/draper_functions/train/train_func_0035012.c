rssyl_remove_rss_cb(GtkAction *action, gpointer data)
{
	FolderView *folderview = (FolderView *)data;
	FolderItem *item;
	gchar *name, *message;
	AlertValue aval;

	debug_print("RSSyl: remove_rss_cb\n");

	item = folderview_get_selected_item(folderview);
	g_return_if_fail(item != NULL);
	g_return_if_fail(item->folder != NULL);
	g_return_if_fail( !folder_item_parent(item) );

	name = trim_string(item->folder->name, 32);
	message = g_strdup_printf(_("Really remove the folder tree '%s'?\n"), name);
	aval = alertpanel_full(_("Remove folder tree"), message,
			 GTK_STOCK_CANCEL, _("_Remove"), NULL, FALSE, NULL,
			  ALERT_WARNING, G_ALERTDEFAULT);
	g_free(message);
	g_free(name);

	if (aval != G_ALERTALTERNATE)
		return;

	folderview_unselect(folderview);
	summary_clear_all(folderview->summaryview);

	folder_destroy(item->folder);
}

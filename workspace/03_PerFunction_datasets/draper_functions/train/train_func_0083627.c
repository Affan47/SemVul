remove_mailbox_cb(GtkAction *action, gpointer data)
{
	FolderView *folderview = (FolderView *)data;
	FolderItem *item;
	gchar *name;
	gchar *message;
	AlertValue avalue;

	item = folderview_get_selected_item(folderview);
	g_return_if_fail(item != NULL);
	g_return_if_fail(item->folder != NULL);
	if (folder_item_parent(item)) return;

	name = trim_string(item->folder->name, 32);
	message = g_strdup_printf
		(_("Really remove the mailbox '%s'?\n"
		   "(The messages are NOT deleted from the disk)"), name);
	avalue = alertpanel_full(_("Remove mailbox"), message,
				 GTK_STOCK_CANCEL, _("_Remove"), NULL, FALSE,
				 NULL, ALERT_WARNING, G_ALERTDEFAULT);
	g_free(message);
	g_free(name);
	if (avalue != G_ALERTALTERNATE) return;

	folderview_unselect(folderview);
	summary_clear_all(folderview->summaryview);

	folder_destroy(item->folder);
}

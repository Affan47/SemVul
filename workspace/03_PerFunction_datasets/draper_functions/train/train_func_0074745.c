unsubscribe_cal_cb(GtkAction *action, gpointer data)
{
	FolderView *folderview = (FolderView *)data;
	GtkCMCTree *ctree = GTK_CMCTREE(folderview->ctree);
	FolderItem *item;
	gchar *message;
	AlertValue avalue;
	gchar *old_path;
	gchar *old_id;

	if (!folderview->selected) return;

	item = gtk_cmctree_node_get_row_data(ctree, folderview->selected);
	g_return_if_fail(item != NULL);
	g_return_if_fail(item->path != NULL);
	g_return_if_fail(item->folder != NULL);

	message = g_strdup_printf
		(_("Do you really want to unsubscribe?"));
	avalue = alertpanel_full(_("Delete folder"), message,
		 		 GTK_STOCK_CANCEL, GTK_STOCK_DELETE, NULL,
				 FALSE, NULL, ALERT_WARNING, G_ALERTDEFAULT);
	g_free(message);
	if (avalue != G_ALERTALTERNATE) return;

	Xstrdup_a(old_path, item->path, return);
	old_id = folder_item_get_identifier(item);

	vcal_item_closed(item);

	if (folderview->opened == folderview->selected ||
	    gtk_cmctree_is_ancestor(ctree,
				  folderview->selected,
				  folderview->opened)) {
		summary_clear_all(folderview->summaryview);
		folderview->opened = NULL;
	}

	if (item->folder->klass->remove_folder(item->folder, item) < 0) {
		folder_item_scan(item);
		alertpanel_error(_("Can't remove the folder '%s'."), item->name);
		g_free(old_id);
		return;
	}

	folder_write_list();

	prefs_filtering_delete_path(old_id);
	g_free(old_id);
}

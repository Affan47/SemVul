folderview_close_opened(FolderView *folderview)
{
	if (folderview->opened) {
		FolderItem *olditem;

		olditem = gtk_cmctree_node_get_row_data(GTK_CMCTREE(folderview->ctree),
						      folderview->opened);
		if (olditem) {
			gchar *buf = g_strdup_printf(_("Closing folder %s..."),
				olditem->path ? olditem->path:olditem->name);

			STATUSBAR_PUSH(folderview->mainwin, buf);
			main_window_cursor_wait(folderview->mainwin);
			g_free(buf);
			summary_save_prefs_to_folderitem(folderview->summaryview, olditem);
			summary_show(folderview->summaryview, NULL);
			folder_item_close(olditem);
			main_window_cursor_normal(folderview->mainwin);
			STATUSBAR_POP(folderview->mainwin);
			if (olditem->folder->klass->item_closed)
				olditem->folder->klass->item_closed(olditem);

		}
	}

	if (folderview->opened &&
	    !GTK_CMCTREE_ROW(folderview->opened)->children)
		gtk_cmctree_collapse(GTK_CMCTREE(folderview->ctree), folderview->opened);

	folderview->opened = NULL;
}

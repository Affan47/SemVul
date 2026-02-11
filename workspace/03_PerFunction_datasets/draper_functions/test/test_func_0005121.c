folder_tree_folder_popup_cb (GthFolderTree *folder_tree,
			     GthFileData   *file_data,
			     guint          time,
			     gpointer       user_data)
{
	GthBrowser    *browser = user_data;
	gboolean       sensitive;
	GthFileSource *file_source;

	sensitive = (file_data != NULL);
	_gth_browser_set_action_sensitive (browser, "Folder_Open", sensitive);
	_gth_browser_set_action_sensitive (browser, "Folder_OpenInNewWindow", sensitive);

	_g_object_unref (browser->priv->folder_popup_file_data);
	browser->priv->folder_popup_file_data = _g_object_ref (file_data);

	if (file_data != NULL)
		file_source = gth_main_get_file_source (file_data->file);
	else
		file_source = NULL;
	gth_hook_invoke ("gth-browser-folder-tree-popup-before", browser, file_source, file_data);
	gtk_ui_manager_ensure_update (browser->priv->ui);

	gtk_menu_popup (GTK_MENU (browser->priv->folder_popup),
			NULL,
			NULL,
			NULL,
			NULL,
			3,
			(guint32) time);

	if (file_data != NULL) {
		GtkTreePath *path;

		path = gth_folder_tree_get_path (GTH_FOLDER_TREE (browser->priv->folder_tree), file_data->file);
		gth_folder_tree_select_path (GTH_FOLDER_TREE (browser->priv->folder_tree), path);

		gtk_tree_path_free (path);
	}

	_g_object_unref (file_source);
}

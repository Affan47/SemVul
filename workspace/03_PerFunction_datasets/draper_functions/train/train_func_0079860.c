gedit_file_browser_store_delete (GeditFileBrowserStore *model,
				 GtkTreeIter           *iter,
				 gboolean               trash)
{
	FileBrowserNode *node;
	GList *rows = NULL;
	GeditFileBrowserStoreResult result;

	g_return_val_if_fail (GEDIT_IS_FILE_BROWSER_STORE (model), GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE);
	g_return_val_if_fail (iter != NULL, GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE);
	g_return_val_if_fail (iter->user_data != NULL, GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE);

	node = (FileBrowserNode *) (iter->user_data);

	if (NODE_IS_DUMMY (node))
		return GEDIT_FILE_BROWSER_STORE_RESULT_NO_CHANGE;

	rows = g_list_append(NULL, gedit_file_browser_store_get_path_real (model, node));
	result = gedit_file_browser_store_delete_all (model, rows, trash);

	g_list_free_full (rows, (GDestroyNotify) gtk_tree_path_free);

	return result;
}

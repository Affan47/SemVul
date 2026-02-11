mh_scan_tree(Folder *folder)
{
	FolderItem *item;
	gchar *rootpath;

	cm_return_val_if_fail(folder != NULL, -1);

	if (!folder->node) {
		item = folder_item_new(folder, folder->name, NULL);
		item->folder = folder;
		folder->node = item->node = g_node_new(item);
	} else
		item = FOLDER_ITEM(folder->node->data);

	rootpath = folder_item_get_path(item);
	if (change_dir(rootpath) < 0) {
		g_free(rootpath);
		return -1;
	}
	g_free(rootpath);

	mh_create_tree(folder);
	mh_remove_missing_folder_items(folder);
	mh_scan_tree_recursive(item);

	return 0;
}

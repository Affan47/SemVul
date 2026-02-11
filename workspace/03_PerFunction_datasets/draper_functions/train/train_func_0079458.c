folder_find_item_from_real_path(const gchar *path)
{
	Folder *folder;
	gpointer d[2];
	GList *list = folder_get_list();

	folder = list ? list->data:NULL;

	cm_return_val_if_fail(folder != NULL, NULL);

	d[0] = (gpointer)path;
	d[1] = NULL;
	while (d[1] == NULL && list) {
		folder = FOLDER(list->data);
		g_node_traverse(folder->node, G_PRE_ORDER, G_TRAVERSE_ALL, -1,
			folder_item_find_func_real_path, d);
		list = list->next;
	}
	return d[1];
}

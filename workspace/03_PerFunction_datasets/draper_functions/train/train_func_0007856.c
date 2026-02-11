model_load_directory (GeditFileBrowserStore *model,
		      FileBrowserNode       *node)
{
	FileBrowserNodeDir *dir;
	AsyncNode *async;

	g_return_if_fail (NODE_IS_DIR (node));

	dir = FILE_BROWSER_NODE_DIR (node);


	if (dir->cancellable != NULL)
		file_browser_node_unload (dir->model, node, TRUE);

	node->flags |= GEDIT_FILE_BROWSER_STORE_FLAG_LOADED;
	model_begin_loading (model, node);

	dir->cancellable = g_cancellable_new ();

	async = g_slice_new (AsyncNode);
	async->dir = dir;
	async->cancellable = g_object_ref (dir->cancellable);
	async->original_children = g_slist_copy (dir->children);


	g_file_enumerate_children_async (node->file,
					 STANDARD_ATTRIBUTE_TYPES,
					 G_FILE_QUERY_INFO_NONE,
					 G_PRIORITY_DEFAULT,
					 async->cancellable,
					 (GAsyncReadyCallback)model_iterate_children_cb,
					 async);
}

set_virtual_root_from_file (GeditFileBrowserStore *model,
			    GFile                 *file)
{
	GList *files;
	GList *item;
	FileBrowserNode *parent;
	GFile *check;


	model_clear (model, FALSE);


	files = get_parent_files (model, file);
	parent = model->priv->root;

	for (item = files; item; item = item->next)
	{
		check = G_FILE (item->data);

		parent = model_add_node_from_dir (model, parent, check);
		g_object_unref (check);
	}

	g_list_free (files);
	set_virtual_root_from_node (model, parent);
}

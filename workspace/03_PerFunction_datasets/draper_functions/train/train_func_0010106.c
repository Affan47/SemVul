find_attr_in_store(GtkTreeModel *model,
				      GtkTreePath  *path,
				      GtkTreeIter  *iter,
				      FindAttrInStore *data)
{
	gchar *attr;
	gtk_tree_model_get(model, iter, CUSTOM_ATTR_NAME, &attr, -1);

	if (g_utf8_collate(data->attr, attr)==0) {
		data->path = path;
		data->iter = *iter;
		return TRUE;
	}
	return FALSE;
}

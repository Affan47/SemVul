pathToIndex(GtkTreePath *path)
{
	gint *indices;

	if (!path)
		return -1;

	indices = gtk_tree_path_get_indices(path);
	return indices[0];
}

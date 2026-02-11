vflist_find_row_cb(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
	ViewFileFindRowData *find = data;
	FileData *fd;
	gtk_tree_model_get(model, iter, FILE_COLUMN_POINTER, &fd, -1);
	if (fd == find->fd)
		{
		*find->iter = *iter;
		find->found = TRUE;
		return TRUE;
		}
	find->row++;
	return FALSE;
}

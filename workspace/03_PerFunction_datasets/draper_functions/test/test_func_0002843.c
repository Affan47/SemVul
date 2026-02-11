allow_selection(GtkTreeSelection * selection,
			    GtkTreeModel * model,
			    GtkTreePath * path,
			    gboolean path_currently_selected,
			    gpointer data)
{
	GtkTreeIter iter;
	VarEntry *ve;

	(void)selection; (void)data; (void)path_currently_selected;

	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);

	if (ve == NULL)
		return FALSE;

	if (ve->type == tifiles_folder_type(GFMFile.model))
		return FALSE;

	if(ve->type == tifiles_flash_type(GFMFile.model))
		return FALSE;

	return TRUE;
}

cb_tree_started(GtkCellRenderer *renderer, GtkCellEditable *editable, gchar *spath, gTree *tree)
{
	GtkTreePath *path = gtk_tree_path_new_from_string(spath);
	if (path)
		tree->_edited_row = tree->pathToKey(path);
	else
		tree->_edited_row = NULL;
}

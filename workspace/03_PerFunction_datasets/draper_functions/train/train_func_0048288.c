gtt_projects_tree_get_col_width (GttProjectsTree *gpt, int col)
{
	g_return_val_if_fail (col >= 0, 0);

	GtkTreeViewColumn *column = gtk_tree_view_get_column (GTK_TREE_VIEW (gpt), col);
	if (column == NULL)
	{
		return -1;
	}
	return gtk_tree_view_column_get_width (column);
}

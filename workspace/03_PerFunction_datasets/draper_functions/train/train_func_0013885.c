results_summary_on_row_activate(GtkTreeView * tree_view, GtkTreePath * path, GtkTreeViewColumn * column
					    __attribute__ ((unused)), gpointer user_data __attribute__ ((unused)))
{
	gboolean expanded = gtk_tree_view_row_expanded(tree_view, path);
	if (!expanded) {
		gtk_tree_view_expand_row(tree_view, path, 1);
	} else {
		gtk_tree_view_collapse_row(tree_view, path);
	}
}

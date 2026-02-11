on_search_widget_activate (GtkWidget *search, gpointer user_data)
{
	GcrListSelector *self = GCR_LIST_SELECTOR (user_data);
	GtkTreePath *path;
	GtkTreeViewColumn *focus_column;

	gtk_tree_view_get_cursor (GTK_TREE_VIEW (self), &path, &focus_column);
	if (path != NULL) {
		gtk_tree_view_row_activated (GTK_TREE_VIEW (self), path, focus_column);
		gtk_tree_path_free (path);

		gtk_widget_hide (search);
	}
}

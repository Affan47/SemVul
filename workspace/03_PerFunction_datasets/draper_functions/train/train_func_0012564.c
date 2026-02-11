activate_selected_row_idle_cb (gpointer data)
{
  GtkTreeView *tree = GTK_TREE_VIEW (data);
  GtkTreeViewColumn *column;
  GtkTreePath *path;

  path = NULL;
  gtk_tree_view_get_cursor (tree, &path, &column);
  if (path) {
    if (!column)
      column = gtk_tree_view_get_column (tree, 0);
    gtk_tree_view_row_activated (tree, path, column);
  }


  gtk_tree_path_free (path);

  return FALSE;
}

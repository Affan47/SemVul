tree_view_activate_focused_row (GtkTreeView *view)
{
  GtkTreePath        *path;
  GtkTreeViewColumn  *column;

  gtk_tree_view_get_cursor (view, &path, &column);
  if (path) {
    gtk_tree_view_row_activated (view, path, column);
    gtk_tree_path_free (path);
  }
}

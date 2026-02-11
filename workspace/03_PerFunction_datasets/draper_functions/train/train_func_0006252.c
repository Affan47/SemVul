queue_remove(struct worklist_data *ptr)
{
  GtkTreePath *path;
  GtkTreeViewColumn *col;

  gtk_tree_view_get_cursor(GTK_TREE_VIEW(ptr->dst_view), &path, &col);
  if (path) {
    dst_row_callback(GTK_TREE_VIEW(ptr->dst_view), path, col, ptr);
    gtk_tree_path_free(path);
  }
}

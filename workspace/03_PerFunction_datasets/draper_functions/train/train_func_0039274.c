row_activated_lcb (GtkWidget *widget, GtkTreePath *path,
				   GtkTreeViewColumn *col, gpointer data)
{
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected (sel, NULL, &iter))
    playlist_play (gtk_tree_path_get_indices (path)[0]);

  return FALSE;
}

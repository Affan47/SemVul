candidate_on_cursor_changed(GtkWidget *widget,
			    Candidate *candidate)
{
  GtkTreePath *path;

  gtk_tree_view_get_cursor(GTK_TREE_VIEW(widget), &path, NULL);
  if (path != NULL)
    {
      int *indices;
      indices = gtk_tree_path_get_indices(path);
      candidate->current = candidate->first + indices[0];
      gtk_tree_path_free(path);
    }
}

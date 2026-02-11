expand_cell_data_func (GtkTreeViewColumn *column,
                       GtkCellRenderer *renderer,
                       GtkTreeModel *model,
                       GtkTreeIter *iter,
                       gpointer )
{
  GtkTreePath *path = NULL;
  gint column_type;
  gboolean row_expanded = FALSE;

  path = gtk_tree_model_get_path (model, iter);
  row_expanded = gtk_tree_view_row_expanded (GTK_TREE_VIEW (gtk_tree_view_column_get_tree_view (column)), path);
  gtk_tree_path_free (path);

  gtk_tree_model_get (model, iter, COLUMN_TYPE, &column_type, -1);

  if (column_type == TYPE_PRESENTITY || column_type == TYPE_HEAP)
    g_object_set (renderer, "visible", FALSE, NULL);
  else
    g_object_set (renderer, "visible", TRUE, NULL);

  g_object_set (renderer,
                "expander-style", row_expanded ? GTK_EXPANDER_EXPANDED : GTK_EXPANDER_COLLAPSED,
                NULL);
}

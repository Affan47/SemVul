find_row (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
  gchar **directory = data;
  gchar *string;

  gtk_tree_model_get (model, iter, COLUMN_CANONICAL_PATH, &string, -1);

  if (g_strcmp0 (string, *directory) == 0)
    {
      g_free (*directory);
      *directory = NULL;
      return TRUE;
    }

  return FALSE;
}

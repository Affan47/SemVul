egg_column_model_get_iter (GtkTreeModel *tree_model,
			   GtkTreeIter  *iter,
			   GtkTreePath  *path)
{
  EggColumnModel *column_model = (EggColumnModel *) tree_model;
  GList *list;
  gint i;

  i = gtk_tree_path_get_indices (path)[0];
  list = g_list_nth (column_model->columns, i);

  if (list == NULL)
  {

	  return FALSE;
  }
  iter->stamp = column_model->stamp;
  iter->user_data = list;

  return TRUE;
}

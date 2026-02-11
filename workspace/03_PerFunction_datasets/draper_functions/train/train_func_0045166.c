toggled_default_inmd(GtkCellRendererToggle *cell, gchar *path_string, gpointer data)
{
  GtkTreeModel *model = GTK_TREE_MODEL (data);
  clear_col_default_inmd(model);
  GtkTreeIter iter;
  GtkTreePath *path = gtk_tree_path_new_from_string (path_string);


  gtk_tree_model_get_iter (model, &iter, path);
  char *key;
  gtk_tree_model_get (model, &iter, COLUMN_KEY, &key, -1);
  char *file;
  gtk_tree_model_get (model, &iter, COLUMN_FILE, &file, -1);
  char tt[128];
  sprintf(tt, "%s %s", key, file);
  free(default_input_method_str);
  default_input_method_str = strdup(tt);
  dbg("default_input_method_str %s\n", default_input_method_str);


  gtk_list_store_set (GTK_LIST_STORE (model), &iter, COLUMN_DEFAULT_INMD, TRUE, -1);
  gtk_list_store_set (GTK_LIST_STORE (model), &iter, COLUMN_USE, TRUE, -1);

  gtk_tree_path_free (path);

  return TRUE;
}

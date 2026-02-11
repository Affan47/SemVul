ensure_something_selected_foreach_cb (GtkTreeModel  *model,
                                      GtkTreePath   *path,
                                      GtkTreeIter   *iter,
                                      gpointer       user_data)
{
  UDisksObject **object = user_data;
  gtk_tree_model_get (model, iter,
                      GDU_DEVICE_TREE_MODEL_COLUMN_OBJECT, object,
                      -1);
  if (*object != NULL)
    return TRUE;
  return FALSE;
}

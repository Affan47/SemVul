egg_column_model_iter_has_child (GtkTreeModel *tree_model,
				 GtkTreeIter  *iter)
{
  g_return_val_if_fail (EGG_IS_COLUMN_MODEL (tree_model), FALSE);
  g_return_val_if_fail (iter->stamp == EGG_COLUMN_MODEL (tree_model)->stamp, FALSE);

  return FALSE;
}

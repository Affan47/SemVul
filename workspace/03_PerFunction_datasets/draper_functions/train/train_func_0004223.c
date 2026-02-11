custom_list_iter_n_children (GtkTreeModel *tree_model,
                             GtkTreeIter  *iter)
{
  CustomList  *custom_list;

  g_return_val_if_fail (CUSTOM_IS_LIST (tree_model), -1);
  g_return_val_if_fail (iter == NULL || iter->user_data != NULL, FALSE);

  custom_list = CUSTOM_LIST(tree_model);


  if (!iter)
    return custom_list->num_rows;

  return 0;
}

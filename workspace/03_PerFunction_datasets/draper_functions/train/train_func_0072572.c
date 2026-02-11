nodes_table_clear(GtkWidget *window)
{

  GtkTreeView *gv;
  GtkTreeModel *sort_model;
  GtkTreeModel *gls;
  GtkTreeIter it;
  gboolean res;

  gv = retrieve_treeview(window);
  if (!gv)
    return;


  sort_model = gtk_tree_view_get_model(gv);
  if (!sort_model)
    return;


  gls = gtk_tree_model_sort_get_model(GTK_TREE_MODEL_SORT(sort_model));
  if (!gls)
    return;

  res = gtk_tree_model_get_iter_first (gls, &it);
  while (res)
    {
      node_id_t *rowitem = NULL;
      gtk_tree_model_get (gls, &it,
                          NODES_COLUMN_N, &rowitem, -1);
      g_free(rowitem);
      res = gtk_list_store_remove (GTK_LIST_STORE(gls), &it);
    }
}

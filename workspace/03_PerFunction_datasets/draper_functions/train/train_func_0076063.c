protocols_table_clear(GtkListStore *gs)
{
  gboolean res;
  GtkTreeIter it;

  res = gtk_tree_model_get_iter_first (GTK_TREE_MODEL (gs), &it);
  while (res)
    {
      protocol_list_item_t *row_proto = NULL;
      gtk_tree_model_get (GTK_TREE_MODEL (gs), &it, PROTO_COLUMN_N,
                          &row_proto, -1);
      if (row_proto)
        {
          g_free(row_proto->name);
          g_free(row_proto);
          res = gtk_list_store_remove (gs, &it);
        }
    }
}

plugin_icon_data_func (GtkTreeViewColumn *column,
                       GtkCellRenderer   *cell,
                       GtkTreeModel      *model,
                       GtkTreeIter       *iter)
{
  GIcon *icon_gicon;
  gchar *icon_stock_id;

  gtk_tree_model_get (model, iter,
    PEAS_GTK_PLUGIN_MANAGER_STORE_ICON_GICON_COLUMN, &icon_gicon,
    PEAS_GTK_PLUGIN_MANAGER_STORE_ICON_STOCK_ID_COLUMN, &icon_stock_id,
    -1);

  if (icon_gicon == NULL)
    {
      g_object_set (cell, "stock-id", icon_stock_id, NULL);
    }
  else
    {
      g_object_set (cell, "gicon", icon_gicon, NULL);
      g_object_unref (icon_gicon);
    }

  g_free (icon_stock_id);
}

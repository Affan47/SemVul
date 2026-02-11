exo_icon_bar_row_inserted (GtkTreeModel *model,
                           GtkTreePath  *path,
                           GtkTreeIter  *iter,
                           ExoIconBar   *icon_bar)
{
  ExoIconBarItem  *item;
  GList           *lp;
  gint             idx;

  idx = gtk_tree_path_get_indices (path)[0];
  item = exo_icon_bar_item_new ();

  if ((gtk_tree_model_get_flags (icon_bar->priv->model) & GTK_TREE_MODEL_ITERS_PERSIST) != 0)
    item->iter = *iter;
  item->index = idx;

  icon_bar->priv->items = g_list_insert (icon_bar->priv->items, item, idx);

  for (lp = g_list_nth (icon_bar->priv->items, idx + 1); lp != NULL; lp = lp->next)
    {
      item = lp->data;
      item->index++;
    }

  gtk_widget_queue_resize (GTK_WIDGET (icon_bar));
}

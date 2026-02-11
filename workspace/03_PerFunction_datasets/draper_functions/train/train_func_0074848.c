exo_icon_bar_get_item_icon (ExoIconBar      *icon_bar,
                            ExoIconBarItem  *item)
{
  GtkTreePath *path;
  GtkTreeIter  iter;
  GdkPixbuf   *pixbuf;

  if ((gtk_tree_model_get_flags (icon_bar->priv->model) & GTK_TREE_MODEL_ITERS_PERSIST) == 0)
    {
      path = gtk_tree_path_new_from_indices (item->index, -1);
      gtk_tree_model_get_iter (icon_bar->priv->model, &iter, path);
      gtk_tree_path_free (path);
    }
  else
    {
      iter = item->iter;
    }

  gtk_tree_model_get (icon_bar->priv->model, &iter,
                      icon_bar->priv->pixbuf_column, &pixbuf,
                      -1);

  return pixbuf;
}

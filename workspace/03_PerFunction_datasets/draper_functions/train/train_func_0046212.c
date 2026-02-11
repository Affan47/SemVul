exo_icon_view_get_visible_range (const ExoIconView *icon_view,
                                 GtkTreePath      **start_path,
                                 GtkTreePath      **end_path)
{
  const ExoIconViewPrivate *priv = icon_view->priv;
  const ExoIconViewItem    *item;
  const GList              *lp;
  gint                      start_index = -1;
  gint                      end_index = -1;
  gint                      i;

  g_return_val_if_fail (EXO_IS_ICON_VIEW (icon_view), FALSE);

  if (priv->hadjustment == NULL || priv->vadjustment == NULL)
    return FALSE;

  if (start_path == NULL && end_path == NULL)
    return FALSE;

  for (i = 0, lp = priv->items; lp != NULL; ++i, lp = lp->next)
    {
      item = (const ExoIconViewItem *) lp->data;
      if ((item->area.x + item->area.width >= (gint) gtk_adjustment_get_value(priv->hadjustment)) &&
          (item->area.y + item->area.height >= (gint) gtk_adjustment_get_value(priv->vadjustment)) &&
          (item->area.x <= (gint) (gtk_adjustment_get_value(priv->hadjustment) + gtk_adjustment_get_page_size(priv->hadjustment))) &&
          (item->area.y <= (gint) (gtk_adjustment_get_value(priv->vadjustment) + gtk_adjustment_get_page_size(priv->vadjustment))))
        {
          if (start_index == -1)
            start_index = i;
          end_index = i;
        }
    }

  if (start_path != NULL && start_index != -1)
    *start_path = gtk_tree_path_new_from_indices (start_index, -1);
  if (end_path != NULL && end_index != -1)
    *end_path = gtk_tree_path_new_from_indices (end_index, -1);

  return (start_index != -1);
}

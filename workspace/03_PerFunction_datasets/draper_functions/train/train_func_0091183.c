exo_icon_view_update_rubberband_selection (ExoIconView *icon_view)
{
  ExoIconViewItem *item;
  gboolean         selected;
  gboolean         changed = FALSE;
  gboolean         is_in;
  GList           *lp;
  gint             x, y;
  gint             width;
  gint             height;


  x = MIN (icon_view->priv->rubberband_x_1, icon_view->priv->rubberband_x2);
  y = MIN (icon_view->priv->rubberband_y_1, icon_view->priv->rubberband_y2);
  width = ABS (icon_view->priv->rubberband_x_1 - icon_view->priv->rubberband_x2);
  height = ABS (icon_view->priv->rubberband_y_1 - icon_view->priv->rubberband_y2);


  for (lp = icon_view->priv->items; lp != NULL; lp = lp->next)
    {
      item = EXO_ICON_VIEW_ITEM (lp->data);

      is_in = exo_icon_view_item_hit_test (icon_view, item, x, y, width, height);

      selected = is_in ^ item->selected_before_rubberbanding;

      if (G_UNLIKELY (item->selected != selected))
        {
          changed = TRUE;
          item->selected = selected;
          exo_icon_view_queue_draw_item (icon_view, item);
        }
    }

  if (G_LIKELY (changed))
    g_signal_emit (G_OBJECT (icon_view), icon_view_signals[SELECTION_CHANGED], 0);
}

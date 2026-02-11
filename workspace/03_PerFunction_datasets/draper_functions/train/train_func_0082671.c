exo_icon_view_select_item (ExoIconView      *icon_view,
                           ExoIconViewItem  *item)
{
  if (item->selected || icon_view->priv->selection_mode == GTK_SELECTION_NONE)
    return;
  else if (icon_view->priv->selection_mode != GTK_SELECTION_MULTIPLE)
    exo_icon_view_unselect_all_internal (icon_view);

  item->selected = TRUE;

  exo_icon_view_queue_draw_item (icon_view, item);

  g_signal_emit (icon_view, icon_view_signals[SELECTION_CHANGED], 0);
}

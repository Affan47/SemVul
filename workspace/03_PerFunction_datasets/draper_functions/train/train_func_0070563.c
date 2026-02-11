exo_icon_view_select_all_between (ExoIconView     *icon_view,
                                  ExoIconViewItem *anchor,
                                  ExoIconViewItem *cursor)
{
  GList *items;
  ExoIconViewItem *item, *last;
  gboolean dirty = FALSE;

  for (items = icon_view->priv->items; items; items = items->next)
    {
      item = items->data;

      if (item == anchor)
        {
          last = cursor;
          break;
        }
      else if (item == cursor)
        {
          last = anchor;
          break;
        }
    }

  for (; items; items = items->next)
    {
      item = items->data;

      if (!item->selected)
      {
        dirty = TRUE;
        item->selected = TRUE;
        exo_icon_view_item_selected_changed (icon_view, item);
      }

      exo_icon_view_queue_draw_item (icon_view, item);

      if (item == last)
        break;
    }

  return dirty;
}

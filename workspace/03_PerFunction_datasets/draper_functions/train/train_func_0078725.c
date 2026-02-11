bonobo_dock_layout_add_floating_item (BonoboDockLayout *layout,
                                     BonoboDockItem *item,
                                     gint x, gint y,
                                     GtkOrientation orientation)
{
  BonoboDockLayoutItem *new;

  new = g_new (BonoboDockLayoutItem, 1);
  new->item = item;
  new->placement = BONOBO_DOCK_FLOATING;
  new->position.floating.x = x;
  new->position.floating.y = y;
  new->position.floating.orientation = orientation;

  layout->items = g_list_prepend (layout->items, new);

  g_object_ref (item);

  return TRUE;
}

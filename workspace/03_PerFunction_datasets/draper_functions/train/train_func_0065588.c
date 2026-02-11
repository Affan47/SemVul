on_motion_notify_event_cb (GooCanvasItem  *item,
                           GooCanvasItem  *target_item,
                           GdkEventMotion *event,
                           gpointer user_data)
{
  if (drag_item == item && drag_item != NULL)
  {
    gdouble rel_x = event->x - drag_x;
    gdouble rel_y = event->y - drag_y;

    if (drag_mode == MODE_MOVE)
    {
      g_object_set (G_OBJECT (item), "x", item_x + rel_x, "y", item_y + rel_y, NULL);
    }
    else
    {
      gdouble new_width = MAX (item_width + rel_x, 5.0);
      gdouble new_height = MAX (item_height + rel_y, 5.0);

      g_object_set (G_OBJECT (item), "width", new_width, "height", new_height, NULL);
    }

    return TRUE;
  }

  return FALSE;
}

on_button_press_event_cb (GooCanvasItem *item,
                          GooCanvasItem *target_item,
                          GdkEventButton *event,
                          gpointer user_data)
{
  if (event->state & GDK_CONTROL_MASK)
  {
    if (event->button == 1 || event->button == 3)
    {
      if (event->button == 1)
        drag_mode = MODE_MOVE;
      else
        drag_mode = MODE_RESIZE;

      drag_item = item;
      drag_x = event->x;
      drag_y = event->y;

      g_object_get (G_OBJECT (item),
                    "x", &item_x,
                    "y", &item_y,
                    "width", &item_width,
                    "height", &item_height,
                    NULL);

      goo_canvas_pointer_grab (GOO_CANVAS (user_data), item, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_RELEASE_MASK, NULL, event->time);
      return TRUE;
    }
  }

  return FALSE;
}

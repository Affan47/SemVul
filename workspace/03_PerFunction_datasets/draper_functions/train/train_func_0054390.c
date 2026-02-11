goo_canvas_item_accessible_get_extents (AtkComponent *component,
					gint         *x,
					gint         *y,
					gint         *width,
					gint         *height,
					AtkCoordType  coord_type)
{
  GooCanvasItem *item;
  GooCanvas *canvas;
  GObject *object;
  gint window_x, window_y;
  gint toplevel_x, toplevel_y;
  GdkRectangle rect;
  GdkWindow *window;

  g_return_if_fail (GOO_IS_CANVAS_ITEM_ACCESSIBLE (component));

  *x = *y = G_MININT;

  object = atk_gobject_accessible_get_object (ATK_GOBJECT_ACCESSIBLE (component));
  if (!object)
    return;

  item = GOO_CANVAS_ITEM (object);

  canvas = goo_canvas_item_get_canvas (item);
  if (!canvas || !GTK_WIDGET (canvas)->window)
    return;

  goo_canvas_item_accessible_get_item_extents (item, &rect);
  *width = rect.width;
  *height = rect.height;

  if (!goo_canvas_item_accessible_is_item_in_window (item, &rect))
    return;

  gdk_window_get_origin (GTK_WIDGET (canvas)->window,
			 &window_x, &window_y);
  *x = rect.x + window_x;
  *y = rect.y + window_y;

  if (coord_type == ATK_XY_WINDOW)
    {
      window = gdk_window_get_toplevel (GTK_WIDGET (canvas)->window);
      gdk_window_get_origin (window, &toplevel_x, &toplevel_y);
      *x -= toplevel_x;
      *y -= toplevel_y;
    }
}

gc_item_rotate_relative_with_center(GooCanvasItem *item, double angle, int x, int y)
{
  double x1, x2, y1, y2;

  if(GOO_IS_CANVAS_POLYLINE(item)) {
    GooCanvasPoints *points;
    g_object_get (item, "points", &points, NULL);
    x1 = points->coords[0];
    y1 = points->coords[1];
    x2 = points->coords[2];
    y2 = points->coords[3];
  } else if(GOO_IS_CANVAS_IMAGE(item) || GOO_IS_CANVAS_RECT(item)) {
    g_object_get (item, "x", &x1, NULL);
    g_object_get (item, "y", &y1, NULL);
    g_object_get (item, "width",  &x2, NULL);
    g_object_get (item, "height", &y2, NULL);
    x2 += x1 + (x2 - x1);
    y2 += y1 + (y2 - y1);
  } else if(GOO_IS_CANVAS_GROUP(item)){
    g_object_get (item, "x", &x1, NULL);
    g_object_get (item, "y", &y1, NULL);
    x2 = x1;
    y2 = y1;
  } else {
    g_object_get (item, "x1", &x1, NULL);
    g_object_get (item, "y1", &y1, NULL);
    g_object_get (item, "x2", &x2, NULL);
    g_object_get (item, "y2", &y2, NULL);
  }

  goo_canvas_item_rotate(item, angle, x1+x, y1+y);
}

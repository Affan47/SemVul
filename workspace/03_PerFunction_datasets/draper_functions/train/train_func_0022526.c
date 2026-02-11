goo_canvas_update_automatic_bounds (GooCanvas       *canvas)
{
  GooCanvasBounds bounds = { 0.0, 0.0, GOO_CANVAS_DEFAULT_WIDTH,
			     GOO_CANVAS_DEFAULT_HEIGHT };

  if (canvas->root_item)
    goo_canvas_item_get_bounds (canvas->root_item, &bounds);


  if (canvas->bounds_from_origin)
    {
      bounds.x1 = 0.0;
      bounds.y1 = 0.0;
      bounds.x2 += canvas->bounds_padding;
      bounds.y2 += canvas->bounds_padding;
    }
  else
    {
      bounds.x1 -= canvas->bounds_padding;
      bounds.y1 -= canvas->bounds_padding;
      bounds.x2 += canvas->bounds_padding;
      bounds.y2 += canvas->bounds_padding;
    }


  if (bounds.x2 < bounds.x1)
    bounds.x2 = bounds.x1;
  if (bounds.y2 < bounds.y1)
    bounds.y2 = bounds.y1;


  if (bounds.x1 != canvas->bounds.x1
      || bounds.y1 != canvas->bounds.y1
      || bounds.x2 != canvas->bounds.x2
      || bounds.y2 != canvas->bounds.y2)
    {
      canvas->bounds = bounds;
      reconfigure_canvas (canvas, FALSE);
      gtk_widget_queue_draw (GTK_WIDGET (canvas));
    }
}

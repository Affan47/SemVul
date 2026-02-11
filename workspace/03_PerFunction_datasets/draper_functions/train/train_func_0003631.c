goo_canvas_widget_update  (GooCanvasItemSimple *simple,
			   cairo_t             *cr)
{
  GooCanvasWidget *witem = (GooCanvasWidget*) simple;
  gdouble width, height;

  if (witem->widget)
    {
      goo_canvas_widget_get_widget_size (witem, &width, &height);

      simple->bounds.x1 = witem->x;
      simple->bounds.y1 = witem->y;

      simple->bounds.x1 -=
        goo_canvas_widget_anchor_horizontal_pos (witem->anchor, width);
      simple->bounds.y1 -=
        goo_canvas_widget_anchor_vertical_pos (witem->anchor, height);

      simple->bounds.x2 = simple->bounds.x1 + width;
      simple->bounds.y2 = simple->bounds.y1 + height;


      gtk_widget_queue_resize (witem->widget);
    }
  else
    {
      simple->bounds.x1 = simple->bounds.y1 = 0.0;
      simple->bounds.x2 = simple->bounds.y2 = 0.0;
    }
}

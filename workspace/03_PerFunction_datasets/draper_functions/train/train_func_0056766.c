goo_canvas_text_is_item_at (GooCanvasItemSimple *simple,
			    gdouble              x,
			    gdouble              y,
			    cairo_t             *cr,
			    gboolean             is_pointer_event)
{
  GooCanvasItemSimpleData *simple_data = simple->simple_data;
  GooCanvasText *text = (GooCanvasText*) simple;
  GooCanvasTextPrivate *priv = goo_canvas_text_get_private (text);
  PangoLayout *layout;
  GooCanvasBounds bounds;
  PangoLayoutIter *iter;
  PangoRectangle ink_rect, log_rect;
  int px, py, x1, y1, x2, y2;
  int log_x2, ink_x2, log_y2, ink_y2;
  gdouble origin_x, origin_y;
  gboolean in_item = FALSE;


  if (!text->text_data->text || !text->text_data->text[0])
    return FALSE;

  if (is_pointer_event
      && simple_data->pointer_events & GOO_CANVAS_EVENTS_PAINTED_MASK
      && goo_canvas_text_is_unpainted (simple_data->style))
    return FALSE;


  if (priv->height > 0.0 && y > priv->height)
    return FALSE;

  layout = goo_canvas_text_create_layout (simple_data, text->text_data,
					  text->layout_width, cr, &bounds,
					  &origin_x, &origin_y);


  px = (x - origin_x) * PANGO_SCALE;
  py = (y - origin_y) * PANGO_SCALE;


  iter = pango_layout_get_iter (layout);
  do
    {
      pango_layout_iter_get_line_extents (iter, &ink_rect, &log_rect);


      x1 = MIN (log_rect.x, ink_rect.x);
      y1 = MIN (log_rect.y, ink_rect.y);

      log_x2 = log_rect.x + log_rect.width;
      ink_x2 = ink_rect.x + ink_rect.width;
      x2 = MAX (log_x2, ink_x2);

      log_y2 = log_rect.y + log_rect.height;
      ink_y2 = ink_rect.y + ink_rect.height;
      y2 = MAX (log_y2, ink_y2);

      if (px >= x1 && px < x2 && py >= y1 && py < y2)
	{
	  in_item = TRUE;
	  break;
	}

    } while (pango_layout_iter_next_line (iter));

  pango_layout_iter_free (iter);

  g_object_unref (layout);

  return in_item;
}

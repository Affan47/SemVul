goo_canvas_item_simple_get_items_at (GooCanvasItem  *item,
				     gdouble         x,
				     gdouble         y,
				     cairo_t        *cr,
				     gboolean        is_pointer_event,
				     gboolean        parent_visible,
				     GList          *found_items)
{
  GooCanvasItemSimpleClass *class = GOO_CANVAS_ITEM_SIMPLE_GET_CLASS (item);
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) item;
  GooCanvasItemSimpleData *simple_data = simple->simple_data;
  double user_x = x, user_y = y;
  cairo_matrix_t matrix;
  gboolean add_item = FALSE;

  if (simple->need_update)
    goo_canvas_item_ensure_updated (item);


  if (simple->bounds.x1 > x || simple->bounds.x2 < x
      || simple->bounds.y1 > y || simple->bounds.y2 < y)
    return found_items;


  if (is_pointer_event)
    {
      if (simple_data->pointer_events == GOO_CANVAS_EVENTS_NONE)
	return found_items;
      if (simple_data->pointer_events & GOO_CANVAS_EVENTS_VISIBLE_MASK
	  && (!parent_visible
	      || simple_data->visibility <= GOO_CANVAS_ITEM_INVISIBLE
	      || (simple_data->visibility == GOO_CANVAS_ITEM_VISIBLE_ABOVE_THRESHOLD
		  && simple->canvas->scale < simple_data->visibility_threshold)))
	return found_items;
    }

  cairo_save (cr);
  if (simple_data->transform)
    cairo_transform (cr, simple_data->transform);

  cairo_device_to_user (cr, &user_x, &user_y);


  cairo_get_matrix (cr, &matrix);
  matrix.x0 = matrix.y0 = 0.0;
  cairo_set_matrix (cr, &matrix);


  if (simple_data->clip_path_commands)
    {
      goo_canvas_create_path (simple_data->clip_path_commands, cr);
      cairo_set_fill_rule (cr, simple_data->clip_fill_rule);
      if (!cairo_in_fill (cr, user_x, user_y))
	{
	  cairo_restore (cr);
	  return found_items;
	}
    }

  add_item = class->simple_is_item_at (simple, user_x, user_y, cr,
                                       is_pointer_event);

  cairo_restore (cr);

  if (add_item)
    return g_list_prepend (found_items, item);
  else
    return found_items;
}

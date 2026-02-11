goo_canvas_item_simple_update  (GooCanvasItem   *item,
				gboolean         entire_tree,
				cairo_t         *cr,
				GooCanvasBounds *bounds)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) item;
  GooCanvasItemSimpleData *simple_data = simple->simple_data;
  cairo_matrix_t matrix;
  double x_offset, y_offset;

  if (entire_tree || simple->need_update)
    {

      goo_canvas_request_item_redraw (simple->canvas, &simple->bounds, simple_data->is_static);

      cairo_save (cr);
      if (simple_data->transform)
	cairo_transform (cr, simple_data->transform);


      cairo_get_matrix (cr, &matrix);
      x_offset = matrix.x0;
      y_offset = matrix.y0;
      matrix.x0 = matrix.y0 = 0.0;
      cairo_set_matrix (cr, &matrix);

      goo_canvas_item_simple_update_internal (simple, cr);

      goo_canvas_item_simple_user_bounds_to_device (simple, cr,
						    &simple->bounds);


      simple->bounds.x1 += x_offset;
      simple->bounds.y1 += y_offset;
      simple->bounds.x2 += x_offset;
      simple->bounds.y2 += y_offset;

      cairo_restore (cr);


      goo_canvas_request_item_redraw (simple->canvas, &simple->bounds, simple_data->is_static);
    }

  *bounds = simple->bounds;
}

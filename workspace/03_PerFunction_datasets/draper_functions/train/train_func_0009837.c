goo_canvas_group_move_child    (GooCanvasItem  *item,
				gint	        old_position,
				gint            new_position)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) item;
  GooCanvasGroup *group = (GooCanvasGroup*) item;
  GooCanvasItem *child;
  GooCanvasBounds bounds;


  child = group->items->pdata[old_position];
  if (simple->canvas)
    {
      goo_canvas_item_get_bounds (child, &bounds);
      goo_canvas_request_item_redraw (simple->canvas, &bounds,
				      simple->simple_data->is_static);
    }

  goo_canvas_util_ptr_array_move (group->items, old_position, new_position);

  goo_canvas_item_request_update (item);
}

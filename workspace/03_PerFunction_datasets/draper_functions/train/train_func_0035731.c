goo_canvas_item_simple_get_bounds  (GooCanvasItem   *item,
				    GooCanvasBounds *bounds)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) item;

  if (simple->need_update)
    goo_canvas_item_ensure_updated (item);

  *bounds = simple->bounds;
}

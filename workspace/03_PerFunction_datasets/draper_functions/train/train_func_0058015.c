goo_canvas_get_item_at (GooCanvas     *canvas,
			gdouble        x,
			gdouble        y,
			gboolean       is_pointer_event)
{
  GooCanvasPrivate *priv;
  cairo_t *cr;
  GooCanvasItem *result = NULL;
  GList *list = NULL;

  g_return_val_if_fail (GOO_IS_CANVAS (canvas), NULL);

  priv = GOO_CANVAS_GET_PRIVATE (canvas);
  cr = goo_canvas_create_cairo_context (canvas);

  if (canvas->root_item)
    list = goo_canvas_item_get_items_at (canvas->root_item, x, y, cr,
					 is_pointer_event, TRUE, NULL);

  if (!list && priv->static_root_item)
    {
      gdouble static_x = x, static_y = y;

      goo_canvas_convert_to_static_item_space (canvas, &static_x, &static_y);
      list = goo_canvas_item_get_items_at (priv->static_root_item,
					   static_x, static_y, cr,
					   is_pointer_event, TRUE, NULL);
    }

  cairo_destroy (cr);


  if (list)
    result = list->data;

  g_list_free (list);

  return result;
}

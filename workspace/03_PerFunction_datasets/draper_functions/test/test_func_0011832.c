goo_canvas_item_model_simple_set_style (GooCanvasItemModel *model,
					GooCanvasStyle     *style)
{
  GooCanvasItemModelSimple *smodel = (GooCanvasItemModelSimple*) model;
  GooCanvasItemSimpleData *simple_data = &smodel->simple_data;

  if (simple_data->style)
    g_object_unref (simple_data->style);

  if (style)
    {
      simple_data->style = goo_canvas_style_copy (style);
      simple_data->own_style = TRUE;
    }
  else
    {
      simple_data->style = NULL;
      simple_data->own_style = FALSE;
    }

  _goo_canvas_item_model_emit_changed (model, TRUE);
}

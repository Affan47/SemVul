goo_canvas_item_model_get_n_children (GooCanvasItemModel       *model)
{
  GooCanvasItemModelIface *iface = GOO_CANVAS_ITEM_MODEL_GET_IFACE (model);

  return iface->get_n_children ? iface->get_n_children (model) : 0;
}

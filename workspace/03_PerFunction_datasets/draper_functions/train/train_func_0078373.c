goo_canvas_group_get_private (GooCanvasGroup *group)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) group;

  if (simple->model)
    return GOO_CANVAS_GROUP_MODEL_GET_PRIVATE (simple->model);
  else
    return GOO_CANVAS_GROUP_GET_PRIVATE (group);
}

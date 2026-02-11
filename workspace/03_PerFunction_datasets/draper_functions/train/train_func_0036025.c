gegl_node_set_need_rect (GeglNode *node,
                         gpointer  context_id,
                         const GeglRectangle *rect)
{
  GeglOperationContext *context;

  g_return_if_fail (GEGL_IS_NODE (node));
  g_return_if_fail (context_id != NULL);

  context = gegl_node_get_context (node, context_id);
  gegl_operation_context_set_need_rect (context, rect);
}

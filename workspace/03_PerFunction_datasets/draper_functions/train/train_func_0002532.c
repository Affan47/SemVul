detect (GeglOperation *operation,
        gint           x,
        gint           y)
{
  GeglNode *input_node = gegl_operation_get_source_node (operation, "input");
  GeglNode *aux_node   = gegl_operation_get_source_node (operation, "aux");
  GeglNode *aux2_node  = gegl_operation_get_source_node (operation, "aux2");

  if (input_node)
    input_node = gegl_node_detect (input_node, x, y);
  if (aux_node)
    aux_node = gegl_node_detect (aux_node, x, y);
  if (aux2_node)
    aux2_node = gegl_node_detect (aux2_node, x, y);

  if (aux2_node)
    return aux2_node;
  if (aux_node)
    return aux_node;
  if (input_node)
    return input_node;
  return NULL;
}

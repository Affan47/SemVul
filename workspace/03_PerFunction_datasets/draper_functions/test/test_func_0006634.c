gegl_node_get_operation (const GeglNode *node)
{
  if (node == NULL)
    return NULL;

  if (node->operation == NULL)
    {
      if (node->is_graph)
        return "GraphNode";

      return NULL;
    }

  return GEGL_OPERATION_GET_CLASS (node->operation)->name;
}

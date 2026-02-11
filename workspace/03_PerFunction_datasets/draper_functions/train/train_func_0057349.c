gl_array_next_node (gl_list_t list, gl_list_node_t node)
{
  uintptr_t index = NODE_TO_INDEX (node);
  if (!(index < list->count))

    abort ();
  index++;
  if (index < list->count)
    return INDEX_TO_NODE (index);
  else
    return NULL;
}

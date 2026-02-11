gl_array_node_nx_set_value (gl_list_t list, gl_list_node_t node,
                            const void *elt)
{
  uintptr_t index = NODE_TO_INDEX (node);
  if (!(index < list->count))

    abort ();
  list->elements[index] = elt;
  return 0;
}

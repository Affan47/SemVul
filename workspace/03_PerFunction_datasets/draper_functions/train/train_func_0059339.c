gl_array_nx_add_last (gl_list_t list, const void *elt)
{
  size_t count = list->count;

  if (count == list->allocated)
    if (grow (list) < 0)
      return NULL;
  list->elements[count] = elt;
  list->count = count + 1;
  return INDEX_TO_NODE (count);
}

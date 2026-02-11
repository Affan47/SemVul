gl_array_nx_add_at (gl_list_t list, size_t position, const void *elt)
{
  size_t count = list->count;
  const void **elements;
  size_t i;

  if (!(position <= count))

    abort ();
  if (count == list->allocated)
    if (grow (list) < 0)
      return NULL;
  elements = list->elements;
  for (i = count; i > position; i--)
    elements[i] = elements[i - 1];
  elements[position] = elt;
  list->count = count + 1;
  return INDEX_TO_NODE (position);
}

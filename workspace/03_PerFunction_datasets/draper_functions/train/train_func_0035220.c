grow (gl_list_t list)
{
  size_t new_allocated;
  size_t memory_size;
  const void **memory;

  new_allocated = xtimes (list->allocated, 2);
  new_allocated = xsum (new_allocated, 1);
  memory_size = xtimes (new_allocated, sizeof (const void *));
  if (size_overflow_p (memory_size))

    return -1;
  memory = (const void **) realloc (list->elements, memory_size);
  if (memory == NULL)

    return -1;
  list->elements = memory;
  list->allocated = new_allocated;
  return 0;
}

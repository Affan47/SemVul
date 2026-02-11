handle_start_array (void *ctx)
{
  yajl_value_t *v;
  yajl_value_array_t *a;

  v = value_alloc (YAJL_TYPE_ARRAY);
  if (v == NULL)
    return (STATUS_ABORT);

  a = YAJL_TO_ARRAY (v);
  a->children = NULL;
  a->children_num = 0;

  return ((context_push (ctx, v) == 0) ? STATUS_CONTINUE : STATUS_ABORT);
}

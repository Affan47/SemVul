hes_resolve(const char *name, const char *type)
{
  if (init_context() < 0)
    return NULL;


  if (list)
    free(list);

  list = hesiod_resolve(context, name, type);
  if (!list)
    translate_errors();
  return list;
}

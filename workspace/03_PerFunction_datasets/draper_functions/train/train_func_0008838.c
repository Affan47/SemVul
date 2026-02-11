pass_callback(dlink_node *this_hook, ...)
{
  void *res;
  va_list args;

  if (this_hook->next == NULL)
    return NULL;

  va_start(args, this_hook);
  res = ((CBFUNC *) this_hook->next->data)(args);
  va_end(args);

  return res;
}

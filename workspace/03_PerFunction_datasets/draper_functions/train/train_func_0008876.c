dir_stack_pop (ParseInfo *info)
{
  MarkupDir *retval;

  g_return_val_if_fail (info->dir_stack != NULL, NULL);

  retval = info->dir_stack->data;
  info->dir_stack = g_slist_remove (info->dir_stack, retval);

  return retval;
}

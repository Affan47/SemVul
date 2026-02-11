cmd_listhook (int interactive UNUSED, struct cmdarg **args)
{
  cmdret *ret;
  struct sbuf *buffer;
  struct list_head *hook;
  struct sbuf *cur;

  hook = hook_lookup (ARG_STRING(0));
  if (hook == NULL)
    return cmdret_new (RET_FAILURE, "listhook: unknown hook '%s'", ARG_STRING(0));

  if (list_empty(hook))
    return cmdret_new (RET_FAILURE, " Nothing defined for %s ", ARG_STRING(0));

  buffer = sbuf_new(0);

  list_for_each_entry (cur, hook, node)
    {
      sbuf_printf_concat(buffer, "%s", sbuf_get (cur));
      if (cur->node.next != hook)
        sbuf_printf_concat(buffer, "\n");
    }

  ret = cmdret_new (RET_SUCCESS, "%s", sbuf_get (buffer));
  sbuf_free (buffer);
  return ret;
}

get_merge_function (uniqstr name)
{
  merger_list *syms;
  merger_list head;
  int n;

  if (! glr_parser)
    return 0;

  head.next = merge_functions;
  for (syms = &head, n = 1; syms->next; syms = syms->next, n += 1)
    if (UNIQSTR_EQ (name, syms->next->name))
      break;
  if (syms->next == NULL)
    {
      syms->next = xmalloc (sizeof syms->next[0]);
      syms->next->name = uniqstr_new (name);


      syms->next->type = NULL;
      syms->next->next = NULL;
      merge_functions = head.next;
    }
  return n;
}

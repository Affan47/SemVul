copy_list (const struct format_arg_list *list)
{
  struct format_arg_list *newlist;
  unsigned int length;
  unsigned int i;

  VERIFY_LIST (list);

  newlist = XMALLOC (struct format_arg_list);

  newlist->initial.count = newlist->initial.allocated = list->initial.count;
  length = 0;
  if (list->initial.count == 0)
    newlist->initial.element = NULL;
  else
    {
      newlist->initial.element =
        XNMALLOC (newlist->initial.allocated, struct format_arg);
      for (i = 0; i < list->initial.count; i++)
        {
          copy_element (&newlist->initial.element[i],
                        &list->initial.element[i]);
          length += list->initial.element[i].repcount;
        }
    }
  ASSERT (length == list->initial.length);
  newlist->initial.length = length;

  newlist->repeated.count = newlist->repeated.allocated = list->repeated.count;
  length = 0;
  if (list->repeated.count == 0)
    newlist->repeated.element = NULL;
  else
    {
      newlist->repeated.element =
        XNMALLOC (newlist->repeated.allocated, struct format_arg);
      for (i = 0; i < list->repeated.count; i++)
        {
          copy_element (&newlist->repeated.element[i],
                        &list->repeated.element[i]);
          length += list->repeated.element[i].repcount;
        }
    }
  ASSERT (length == list->repeated.length);
  newlist->repeated.length = length;

  VERIFY_LIST (newlist);

  return newlist;
}

backtrack_in_initial (struct format_arg_list *list)
{
  ASSERT (list->repeated.count == 0);

  while (list->initial.count > 0)
    {
      unsigned int i = list->initial.count - 1;
      if (list->initial.element[i].presence == FCT_REQUIRED)
        {

          list->initial.length -= list->initial.element[i].repcount;
          free_element (&list->initial.element[i]);
          list->initial.count = i;
        }
      else
        {

          list->initial.length--;
          if (list->initial.element[i].repcount > 1)
            list->initial.element[i].repcount--;
          else
            {
              free_element (&list->initial.element[i]);
              list->initial.count = i;
            }
          VERIFY_LIST (list);
          return list;
        }
    }

  free_list (list);
  return NULL;
}

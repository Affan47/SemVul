is_required (const struct format_arg_list *list, unsigned int n)
{
  unsigned int s;
  unsigned int t;


  t = n + 1;


  for (s = 0;
       s < list->initial.count && t >= list->initial.element[s].repcount;
       t -= list->initial.element[s].repcount, s++)
    if (list->initial.element[s].presence != FCT_REQUIRED)
      return false;

  if (t == 0)
    return true;

  if (s < list->initial.count)
    {
      if (list->initial.element[s].presence != FCT_REQUIRED)
        return false;
      else
        return true;
    }


  if (list->repeated.count == 0)
    return false;

  for (s = 0;
       s < list->repeated.count && t >= list->repeated.element[s].repcount;
       t -= list->repeated.element[s].repcount, s++)
    if (list->repeated.element[s].presence != FCT_REQUIRED)
      return false;

  if (t == 0)
    return true;

  if (s < list->repeated.count)
    {
      if (list->repeated.element[s].presence != FCT_REQUIRED)
        return false;
      else
        return true;
    }


  return true;
}

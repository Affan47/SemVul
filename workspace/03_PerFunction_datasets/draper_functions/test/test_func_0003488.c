iconvable_string_list (const iconveh_t *cd, string_list_ty *slp)
{
  size_t i;

  if (slp != NULL)
    for (i = 0; i < slp->nitems; i++)
      if (!iconvable_string (cd, slp->item[i]))
        return false;
  return true;
}

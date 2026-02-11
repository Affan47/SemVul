string_list_equal (const string_list_ty *slp1, const string_list_ty *slp2)
{
  size_t i, i1, i2;

  i1 = (slp1 != NULL ? slp1->nitems : 0);
  i2 = (slp2 != NULL ? slp2->nitems : 0);
  if (i1 != i2)
    return false;
  for (i = 0; i < i1; i++)
    if (strcmp (slp1->item[i], slp2->item[i]) != 0)
      return false;
  return true;
}

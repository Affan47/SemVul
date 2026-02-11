state_compare (state const *s1, state const *s2)
{
  size_t i;

  if (s1->nitems != s2->nitems)
    return false;

  for (i = 0; i < s1->nitems; ++i)
    if (s1->items[i] != s2->items[i])
      return false;

  return true;
}

num_sel_recompute (struct Bond *list)
{
  int n = 0;
  struct Bond * current = list;

  if (list == NULL)
    return 0;

  do
    if (current->selected & SEL_YES)
      n++;
  while ((current = current->next) != NULL);

  return n;
}

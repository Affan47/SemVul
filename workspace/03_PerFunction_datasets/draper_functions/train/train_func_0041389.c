bounds_of_list (struct Bond *list, LLINT * xmin, LLINT * xmax,
		LLINT * ymin, LLINT * ymax)
{
  struct Bond *current;

  *xmin = 2 * prop.global_width;
  *xmax = -2 * prop.global_width;
  *ymin = 2 * prop.global_height;
  *ymax = -2 * prop.global_height;

  current = list;
  do
    bounds_of_bond (current, xmin, xmax, ymin, ymax, 1);
  while ((current = current->next) != NULL);
}

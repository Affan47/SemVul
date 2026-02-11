update_bounds_of_group (struct Bond *group)
{
  LLINT xmin, xmax, ymin, ymax;
  struct Bond *current;

  xmin = 2 * prop.global_width;
  xmax = -2 * prop.global_width;
  ymin = 2 * prop.global_height;
  ymax = -2 * prop.global_height;

  current = group->group_members;
  do
    {
      bounds_of_bond (current, &xmin, &xmax, &ymin, &ymax, 1);
    }
  while ((current = current->next) != NULL);

  group->x1 = xmin;
  group->x2 = xmax;
  group->y1 = ymin;
  group->y2 = ymax;
}

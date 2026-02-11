align_selection (struct Bond *list, const int horizontal, const int vertical)
{
  LLINT xmin, xmax, ymin, ymax, Xmin, Xmax, Ymin, Ymax;
  struct Bond *current;

  if (list == NULL)
    return;

  bounds_of_selection (list, &Xmin, &Xmax, &Ymin, &Ymax);

  current = list;
  do
    {
      if (!(current->selected & SEL_YES))
	continue;

      xmin = 2 * prop.global_width;
      xmax = -2 * prop.global_width;
      ymin = 2 * prop.global_height;
      ymax = -2 * prop.global_height;
      bounds_of_bond (current, &xmin, &xmax, &ymin, &ymax, 0);
      switch (horizontal)
	{
	case 0:
	  break;

	case 1:
	  move_bond_from_pos (current, current, Xmin - xmin, (LLINT) 0);
	  break;

	case 2:
	  move_bond_from_pos (current, current,
			      ((Xmax - xmax) - (xmin - Xmin)) / 2, (LLINT) 0);
	  break;

	case 3:
	  move_bond_from_pos (current, current, Xmax - xmax, (LLINT) 0);
	  break;
	}
      switch (vertical)
	{
	case 0:
	  break;

	case 1:
	  move_bond_from_pos (current, current, (LLINT) 0, Ymin - ymin);
	  break;

	case 2:
	  move_bond_from_pos (current, current, (LLINT) 0,
			      ((Ymax - ymax) - (ymin - Ymin)) / 2);
	  break;

	case 3:
	  move_bond_from_pos (current, current, (LLINT) 0, Ymax - ymax);
	  break;
	}
    }
  while ((current = current->next) != NULL);

  return;
}

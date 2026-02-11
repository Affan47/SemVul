cat_tail_turret_green(const tenm_object *my)
{

  if (my == NULL)
    return 0;

  if (my->count[4] == 0)
    return 0;

  if (my->count[2] == 1)
  {
    if (my->count[3] >= 3160)
      return 0;
    if ((my->count[3] < 250)
        || ((my->count[3] >= 530) && (my->count[3] < 1200))
        || ((my->count[3] >= 1840) && (my->count[3] < 2440)))
    {
      if (my->count[4] == 1)
        return 1;
    }
    else
    {
      if (my->count[4] == 2)
        return 1;
    }
  }

  return 0;
}

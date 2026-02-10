watcher_below_green(const tenm_object *my)
{

  if (my == NULL)
    return 0;

  if ((my->count[2] == 1) && (my->count[4] >= 3)
      && (my->count[3] <= 4100))
    return 1;
  if ((my->count[2] == 2) && (my->count[8] != 0))
    return 1;

  return 0;
}

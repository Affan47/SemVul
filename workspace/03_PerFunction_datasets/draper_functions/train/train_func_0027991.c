perpeki_chip_act(tenm_object *my, const tenm_object *player)
{
  int i;
  int suffix;
  int theta;
  double dx;
  double dy;


  if (my == NULL)
    return 0;
  if (player == NULL)
    return 0;


  my->count[1] += 4;
  if (my->count[1] > WINDOW_HEIGHT + 15)
    return 1;


  for (i = 0; i < my->count[2]; i++)
  {
    suffix = 3 + i * 3;
    if ((my->count[suffix + 1] > my->count[1])
        || (my->count[suffix + 1] <= my->count[1] - 4))
      continue;

    theta = my->count[suffix + 2];
    while (theta >= 360)
      theta -= 360;
    while (theta < 0)
      theta += 360;

    if ((double) (my->count[suffix + 1]) < player->y)
    {
      if (theta > 180)
        theta -= 180;
    }
    else
    {
      if (theta <= 180)
        theta -= 180;
    }

    dx = 15.0 * tenm_cos(theta);
    dy = 15.0 * tenm_sin(theta);
    tenm_table_add(laser_angle_new(my->count[suffix + 0] - dx,
                                   my->count[suffix + 1] - dy,
                                   8.0, theta, 30.0, 4));
  }

  return 0;
}

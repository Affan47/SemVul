last_boss_horizon_act(tenm_object *my, const tenm_object *player)
{

  if (my == NULL)
    return 0;
  if (player == NULL)
    return 0;

  (my->count[2])--;
  if (my->count[2] <= 0)
  {
    tenm_table_add(laser_point_new(my->x, my->y, 15.0,
                                   player->x, player->y,
                                   25.0, 1));

    if (my->count[1] == 0)
    {
      tenm_table_add(laser_new(my->x, my->y, 0.0, 0.0,
                               0.0, 800.0, 5, 7, 0));
    }
    else if (my->count[1] == 1)
    {
      tenm_table_add(laser_new(my->x, my->y, 0.0, 0.0,
                               0.0, -800.0, 5, 7, 0));
    }
    else if (my->count[1] == 2)
    {
      tenm_table_add(laser_new(my->x, my->y, 0.0, 0.0,
                               800.0, 0.0, 5, 7, 0));
    }
    else if (my->count[1] == 3)
    {
      tenm_table_add(laser_new(my->x, my->y, 0.0, 0.0,
                               -800.0, 0.0, 5, 7, 0));
    }
    else
    {
      fprintf(stderr, "last_boss_horizon_act: strange my->count[1] (%d)\n",
              my->count[1]);
    }
    return 1;
  }

  return 0;
}

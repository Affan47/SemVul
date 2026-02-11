silver_chimera_lock_on_act(tenm_object *my, const tenm_object *player)
{
  double length;


  if (my == NULL)
  {
    fprintf(stderr, "silver_chimera_lock_on_act: my is NULL\n");
    return 0;
  }
  if (player == NULL)
    return 0;

  (my->count[2])++;
  switch (my->count[1])
  {
  case 0:
    if (my->count[2] >= 20)
    {
      my->count[1] = 1;
      my->count[2] = 0;
    }
    break;
  case 1:
    length = 5.0 * (double) (140 - my->count[2]);
    if (my->count[2] % 10 == 0)
    {
      if (my->count[2] % 20 == 10 * my->count[3])
      {
        tenm_table_add(laser_angle_new(my->x + length, my->y + length, 9.0,
                                       180, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x + length, my->y + length, 9.0,
                                       -90, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x - length, my->y - length, 9.0,
                                       0, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x - length, my->y - length, 9.0,
                                       90, 25.0, 0));
      }
      else
      {
        tenm_table_add(laser_angle_new(my->x + length, my->y - length, 9.0,
                                       180, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x + length, my->y - length, 9.0,
                                       90, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x - length, my->y + length, 9.0,
                                       0, 25.0, 0));
        tenm_table_add(laser_angle_new(my->x - length, my->y + length, 9.0,
                                       -90, 25.0, 0));
      }
    }
    if (my->count[2] >= 140)
    {
      return 1;
    }
    break;
  default:
    fprintf(stderr, "silver_chimera_lock_on_act: strange my->count[1] (%d)\n",
            my->count[1]);
    break;
  }

  return 0;
}

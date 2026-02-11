last_boss_act_2(tenm_object *my, const tenm_object *player)
{

  if (my == NULL)
    return 0;
  if (player == NULL)
    return 0;

  if (my->count[2] >= 0)
  {
    (my->count[2])++;
    if (my->count[2] == 60)
      tenm_table_add(last_boss_cage_new(1));
    if (my->count[2] == 240)
      tenm_table_add(last_boss_cage_new(2));
    if ((my->count[2] == 390) || (my->count[2] == 510))
      tenm_table_add(last_boss_cage_new(0));

    if (my->count[2] == 538)
      tenm_table_add(normal_shot_point_new(my->x, my->y, 9.0,
                                           player->x, player->y, 3));
    if (my->count[2] >= 629)
    {
      my->count[1] = 0;
      my->count[2] = -1;
      return 0;
    }
    return 0;
  }


  (my->count[2])--;
  if (my->count[2] <= -4030)
  {
    set_background(2);
    clear_chain();
    last_boss_next(my);
    return 0;
  }

  if (my->count[1] == 0)
  {
    tenm_table_add(last_boss_cage_new(0));
  }

  if (my->count[1] % 4 == 0)
  {
    tenm_table_add(normal_shot_point_new(my->x, my->y, 9.0,
                                         player->x
                                         + (double) (-50 + (rand() % 101)),
                                         player->y
                                         + (double) (-50 + (rand() % 101)),
                                         3));
  }

  (my->count[1])++;
  if (my->count[1] >= 120)
    my->count[1] = 0;

  return 0;
}

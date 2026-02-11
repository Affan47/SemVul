w_ko_lock_on_act(tenm_object *my, const tenm_object *player)
{
  int i;


  if (my == NULL)
  {
    fprintf(stderr, "w_ko_lock_on_act: my is NULL\n");
    return 0;
  }
  if (player == NULL)
    return 0;

  (my->count[1])++;
  if (my->count[1] > 30)
  {
    for (i = 0; i < 360; i += 60)
    {
      tenm_table_add(normal_shot_angle_new(my->x, my->y, 5.5,
                                           my->count[2] * 30 + i, 0));
      tenm_table_add(normal_shot_angle_new(my->x, my->y, 3.5,
                                           my->count[2] * 30 + i, 0));
    }

    return 1;
  }

  return 0;
}

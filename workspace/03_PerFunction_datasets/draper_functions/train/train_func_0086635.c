silver_chimera_bit_hit(tenm_object *my, tenm_object *your)
{
  int n;


  if (my == NULL)
  {
    fprintf(stderr, "silver_chimera_bit_hit: my is NULL\n");
    return 0;
  }
  if (your == NULL)
  {
    fprintf(stderr, "silver_chimera_bit_hit: your is NULL\n");
    return 0;
  }

  if (!(your->attr & ATTR_PLAYER_SHOT))
    return 0;
  if (my->count[2] != 1)
    return 0;

  deal_damage(my, your, 0);
  if (silver_chimera_bit_green(my))
    add_chain(my, your);
  my->count[1] = 41;

  if (my->hit_point <= 0)
  {
    add_score(20000);
    tenm_table_apply(my->count[5],
                     (int (*)(tenm_object *, int))
                     (&silver_chimera_bit_signal),
                     0);

    if (silver_chimera_bit_green(my))
      n = 8;
    else
      n = 7;
    tenm_table_add(explosion_new(my->x, my->y,
                                 my->count_d[0] * 0.5,
                                 my->count_d[1] * 0.5,
                                 1, 1000, n, 8.0, 6));
    tenm_table_add(fragment_new(my->x, my->y,
                                my->count_d[0] * 0.5, my->count_d[1] * 0.5,
                                30.0, 30, n, 5.0, 0.0, 20));
    return 1;
  }

  return 0;
}

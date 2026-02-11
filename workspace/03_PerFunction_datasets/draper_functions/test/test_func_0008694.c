senator_hit(tenm_object *my, tenm_object *your)
{

  if (my == NULL)
    return 0;
  if (your == NULL)
    return 0;

  if (!(your->attr & ATTR_PLAYER_SHOT))
    return 0;
  if ((my->count[7] != 1) && (my->count[7] != 3))
    return 0;

  deal_damage(my, your, 0);
  if (senator_green(my))
    add_chain(my, your);
  my->count[1] = 41;

  if (my->hit_point <= 0)
  {
    senator_explode(my);
    add_score(15000);
    tenm_table_apply(my->count[6],
                     (int (*)(tenm_object *, int)) (&senator_signal),
                     my->table_index);
    return 1;
  }

  return 0;
}

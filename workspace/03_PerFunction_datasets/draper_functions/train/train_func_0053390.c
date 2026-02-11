silver_chimera_hit(tenm_object *my, tenm_object *your)
{

  if (my == NULL)
  {
    fprintf(stderr, "silver_chimera_hit: my is NULL\n");
    return 0;
  }
  if (your == NULL)
  {
    fprintf(stderr, "silver_chimera_hit: your is NULL\n");
    return 0;
  }

  if (!(your->attr & ATTR_PLAYER_SHOT))
    return 0;
  if (my->count[2] != 1)
    return 0;

  deal_damage(my, your, 0);
  if (silver_chimera_green(my))
    add_chain(my, your);
  my->count[1] = 2;

  if (my->hit_point <= 0)
  {
    set_background(1);
    silver_chimera_explode(my);
    add_score(30000);
    return 0;
  }

  return 0;
}

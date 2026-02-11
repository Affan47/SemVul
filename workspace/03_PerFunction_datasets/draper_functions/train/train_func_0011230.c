stage_clear_act(tenm_object *my, const tenm_object *player)
{
  int stage;


  if (my == NULL)
  {
    fprintf(stderr, "stage_clear_act: my is NULL\n");
    return 0;
  }
  if (player == NULL)
    return 0;

  if (get_ship() < 0)
    return 1;

  (my->count[0])++;
  if (my->count[0] == 0)
  {
    stage = get_stage_number();
    if ((stage >= 1) && (stage <= 5))
      set_stage_cleared(stage, 1);
  }
  if (my->count[0] >= my->count[1] + 100)
  {
    set_this_stage_cleared(1);
    return 1;
  }

  return 0;
}

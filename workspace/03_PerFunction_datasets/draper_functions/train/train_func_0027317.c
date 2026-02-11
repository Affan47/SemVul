game_record_new(int stage_n, int plan_n, int valid)
{
  int i;
  game_record *new = NULL;


  if (stage_n <= 0)
  {
    fprintf(stderr, "game_record_new: stage_n is non-positive (%d)\n",
            stage_n);
    return NULL;
  }
  if (plan_n <= 0)
  {
    fprintf(stderr, "game_record_new: plan_n is non-positive (%d)\n",
            plan_n);
    return NULL;
  }

  new = (game_record *) malloc(sizeof(game_record));
  if (new == NULL)
  {
    fprintf(stderr, "game_record_new: malloc failed\n");
    return NULL;
  }

  new->total_p = NULL;
  new->plan_p = NULL;
  new->plan_n = -1;

  new->total_p = total_record_new(stage_n, valid);
  if (new->total_p == NULL)
  {
    fprintf(stderr, "game_record_new: total_record_new failed\n");
    game_record_delete(new);
    return NULL;
  }
  new->plan_p = (plan_record **) malloc(sizeof(plan_record *) * (plan_n + 1));
  if (new->plan_p == NULL)
  {
    fprintf(stderr, "game_record_new: malloc(plan_p) failed\n");
    game_record_delete(new);
    return NULL;
  }
  for (i = 0; i <= plan_n; i++)
    new->plan_p[i] = NULL;
  for (i = 0; i <= plan_n; i++)
  {
    new->plan_p[i] = plan_record_new(valid);
    if (new->plan_p[i] == NULL)
    {
      fprintf(stderr, "game_record_new: plan_record_new(%d) failed\n", i);
      game_record_delete(new);
      return NULL;
    }
  }

  new->plan_n = plan_n;
  return new;
}

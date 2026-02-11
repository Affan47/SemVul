total_record_new(int stage_n, int valid)
{
  int i;
  int timestamp;
  total_record *new = NULL;


  if (stage_n <= 0)
  {
    fprintf(stderr, "total_record_new: stage_n is non-positive (%d)\n",
            stage_n);
    return NULL;
  }

  new = (total_record *) malloc(sizeof(total_record));
  if (new == NULL)
  {
    fprintf(stderr, "total_record_new: malloc failed\n");
    return NULL;
  }

  new->total_score = -1;
  new->total_score_when = -1;
  new->stage_n = -1;
  new->stage_id = NULL;
  new->stage_score = NULL;
  new->stage_cleared = NULL;
  new->number_play = -1;
  new->number_play_when = -1;

  new->stage_id = (int *) malloc(sizeof(int) * stage_n);
  if (new->stage_id == NULL)
  {
    fprintf(stderr, "total_record_new: malloc(stage_id) failed\n");
    total_record_delete(new);
    return NULL;
  }
  new->stage_score = (int *) malloc(sizeof(int) * stage_n);
  if (new->stage_score == NULL)
  {
    fprintf(stderr, "total_record_new: malloc(stage_score) failed\n");
    total_record_delete(new);
    return NULL;
  }
  new->stage_cleared = (int *) malloc(sizeof(int) * stage_n);
  if (new->stage_cleared == NULL)
  {
    fprintf(stderr, "total_record_new: malloc(stage_cleared) failed\n");
    total_record_delete(new);
    return NULL;
  }

  new->stage_n = stage_n;

  for (i = 0; i < stage_n; i++)
  {
    new->stage_id[i] = -1;
    new->stage_score[i] = -1;
    new->stage_cleared[i] = 0;
  }

  if (valid)
  {
    timestamp = (int) (time(NULL));
    if (timestamp < 0)
    {
      fprintf(stderr, "total_record_new: timestamp is negative (%d)\n",
              timestamp);
      timestamp = -1;
    }

    new->total_score = 0;
    new->total_score_when = timestamp;
    new->number_play = 0;
    new->number_play_when = timestamp;

    for (i = 0; i < stage_n; i++)
    {
      new->stage_id[i] = -1;
      new->stage_score[i] = 0;
      new->stage_cleared[i] = 0;
    }
  }

  return new;
}

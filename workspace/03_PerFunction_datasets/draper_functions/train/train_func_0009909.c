jerasure_free_schedule(int **schedule)
{
  int i;

  for (i = 0; schedule[i][0] >= 0; i++) free(schedule[i]);
  free(schedule[i]);
  free(schedule);
}

AI_SetSightClient (void)
{
  edict_t *ent;
  int start, check;

  if (level.sight_client == NULL)
    start = 1;
  else
    start = level.sight_client - g_edicts;

  check = start;
  while (1)
    {
      check++;
      if (check > game.maxclients)
	check = 1;
      ent = &g_edicts[check];
      if (ent->inuse && ent->health > 0 && !(ent->flags & FL_NOTARGET))
	{
	  level.sight_client = ent;
	  return;
	}
      if (check == start)
	{
	  level.sight_client = NULL;
	  return;
	}
    }
}

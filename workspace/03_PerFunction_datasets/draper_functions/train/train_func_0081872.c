processtimer (Uint32 dt)
{

  int i;
  if (texttimer >= 200 * timestep) texttimer = 0;
  if (texttimer > 0) texttimer += dt;
  timer += dt;

  if (fplayer->id == FIGHTER_FALCON)
  {
    fighter [2]->target = fighter [1];
  }
  else
  {
    fighter [2]->target = fighter [0];
    fighter [1]->target = fighter [3];
  }

  bool testb1 = false, testb2 = false;
  for (i = 4; i <= 29; i ++)
  {
    if (fighter [i]->active)
    {
      if (fighter [i]->party == 1)
        testb1 = true;
      if (fighter [i]->party == 2)
        testb2 = true;
    }
  }
  if (!testb1) return 2;
  if (!testb2) return 1;

  for (i = 0; i <= 3; i ++)
  {
    if (!fighter [i]->active && fighter [i]->explode >= 35 * timestep)
    {
      fighter [i]->explode = 0;
      int temp = fighter [i]->fighterkills;
      int tempid = fighter [i]->id;
      fighter [i]->aiinit ();
      if (i == 0)
      {
        playerInit ();
      }
      else
      {
        fighter [i]->newinit (tempid, 0, 200);
      }
      fighter [i]->party = i / 2 + 1;
      fighter [i]->shield = fighter [i]->maxshield;
      fighter [i]->immunity = 50 * timestep;
      fighter [i]->activate ();

      fighter [i]->fighterkills = temp;
      fighter [i]->killed = false;
      if (i <= 1)
      {
        fighter [i]->tl->x = team1x;
        fighter [i]->tl->z = team1y;
      }
      else
      {
        fighter [i]->tl->x = team2x;
        fighter [i]->tl->z = team2y;
      }
      camera = 0;
    }
  }
  return 0;
}

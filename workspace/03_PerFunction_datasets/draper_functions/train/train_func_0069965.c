processtimer (Uint32 dt)
{
  int i;
  if (texttimer >= 200 * timestep) texttimer = 0;
  if (texttimer > 0) texttimer += dt;
  timer += dt;
  for (i = 0; i <= 7; i ++)
  {
    if (fighter [i]->fighterkills >= 10)
    {

      if (i == 0) return 1;
      else return 2;
    }
    if (!fighter [i]->active && fighter [i]->explode >= 35 * timestep)
    {
      fighter [i]->explode = 0;
      int temp = fighter [i]->fighterkills;
      fighter [i]->aiinit ();
      if (i == 0)
      {
        playerInit ();
      }
      else
      {
        fighter [i]->newinit (FIGHTER_FALCON, i + 1, 200);
      }
      fighter [i]->party = i + 1;
      fighter [i]->shield = fighter [i]->maxshield;
      fighter [i]->immunity = 50 * timestep;
      fighter [i]->activate ();

      fighter [i]->fighterkills = temp;
      fighter [i]->killed = false;
      fighter [i]->ammo = 100000;
      for (i = 0; i < missiletypes; i ++)
      {
        fighter [i]->missiles [i] = 0;
      }
      camera = 0;
    }
  }
  return 0;
}

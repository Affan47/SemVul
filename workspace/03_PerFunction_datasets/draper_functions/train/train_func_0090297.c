PlayerTrail_Init (void)
{
  int n;

  if (deathmatch->value  )
    return;

  for (n = 0; n < TRAIL_LENGTH; n++)
    {
      trail[n] = G_Spawn ();
      trail[n]->classname = "player_trail";
    }

  trail_head = 0;
  trail_active = true;
}

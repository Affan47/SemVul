total_score (int num)
{
  int upper_tot;
  int lower_tot;

  upper_tot = 0;
  lower_tot = 0;

  lower_tot = lower_total (num);
  upper_tot = upper_total (num);

  if (game_type == GAME_KISMET && upper_tot >= 78)
    upper_tot += 75;
  else if (game_type == GAME_KISMET && upper_tot >= 71)
    upper_tot += 55;
  else if (upper_tot >= 63)
    upper_tot += 35;

  return (upper_tot + lower_tot);
}

punish_different_free_days (Chromosome chromo)
{

  unsigned penalty = 0;
  unsigned difference;
  unsigned min = 0xFFFFFFFF;

  for (int worker = 0; worker < chromo.width; worker++)
    if (min > chromo.summary.freedays[worker])
      min = chromo.summary.freedays[worker];

  for (int worker = 0; worker < chromo.width; worker++)
    if ((difference = chromo.summary.freedays[worker] - min) > 1)
      penalty +=
	(difference - 1) * penalty_points[bad_free_days_penalty_idx].value;

  return penalty;
}

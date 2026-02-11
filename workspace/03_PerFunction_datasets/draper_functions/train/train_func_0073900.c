punish_different_weekend_number (Chromosome chromo)
{
  unsigned penalty = 0;
  unsigned difference;
  unsigned min = 0xFFFFFFFF;

  for (int worker = 0; worker < chromo.width; worker++)
    if (min > chromo.summary.weekends[worker])
      min = chromo.summary.weekends[worker];

  for (int worker = 0; worker < chromo.width; worker++)
    if ((difference = chromo.summary.weekends[worker] - min) > 1)
      penalty +=
	penalty_points[weekend_injustice_penalty_idx].value *
	(difference - 1);


  return penalty;
}

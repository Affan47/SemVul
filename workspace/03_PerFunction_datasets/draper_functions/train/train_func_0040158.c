compute_dpd (HP4200_Scanner * s, int step_size, int line_end)
{
  int tr, dpd;

  tr = 1   *
    (line_end + ((s->hw_parms.num_tr_pulses + 1) *
		 (2 * s->hw_parms.guard_band_duration +
		  s->hw_parms.pulse_duration + 1) +
		 3 - s->hw_parms.num_tr_pulses));

  if (tr == 0)
    return 0;

  dpd = (((s->hw_parms.fsteps_25_speed * 4) +
	  (s->hw_parms.fsteps_50_speed * 2) +
	  s->hw_parms.steps_to_reverse) * 4 * step_size) % tr;
  dpd = tr - dpd;

  return dpd;
}

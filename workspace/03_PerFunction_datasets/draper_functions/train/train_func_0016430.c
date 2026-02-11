compute_costs (bool speed_p, struct cost_rtxes *rtxes)
{
  unsigned int i;
  int word_move_zero_cost, word_move_cost;

  PUT_MODE (rtxes->target, word_mode);
  SET_SRC (rtxes->set) = CONST0_RTX (word_mode);
  word_move_zero_cost = set_rtx_cost (rtxes->set, speed_p);

  SET_SRC (rtxes->set) = rtxes->source;
  word_move_cost = set_rtx_cost (rtxes->set, speed_p);

  if (LOG_COSTS)
    fprintf (stderr, "%s move: from zero cost %d, from reg cost %d\n",
	     GET_MODE_NAME (word_mode), word_move_zero_cost, word_move_cost);

  for (i = 0; i < MAX_MACHINE_MODE; i++)
    {
      enum machine_mode mode = (enum machine_mode) i;
      int factor = GET_MODE_SIZE (mode) / UNITS_PER_WORD;
      if (factor > 1)
	{
	  int mode_move_cost;

	  PUT_MODE (rtxes->target, mode);
	  PUT_MODE (rtxes->source, mode);
	  mode_move_cost = set_rtx_cost (rtxes->set, speed_p);

	  if (LOG_COSTS)
	    fprintf (stderr, "%s move: original cost %d, split cost %d * %d\n",
		     GET_MODE_NAME (mode), mode_move_cost,
		     word_move_cost, factor);

	  if (FORCE_LOWERING || mode_move_cost >= word_move_cost * factor)
	    {
	      choices[speed_p].move_modes_to_split[i] = true;
	      choices[speed_p].something_to_do = true;
	    }
	}
    }


  if (choices[speed_p].move_modes_to_split[(int) twice_word_mode])
    {
      int zext_cost;


      PUT_MODE (rtxes->source, word_mode);
      zext_cost = set_src_cost (rtxes->zext, speed_p);

      if (LOG_COSTS)
	fprintf (stderr, "%s %s: original cost %d, split cost %d + %d\n",
		 GET_MODE_NAME (twice_word_mode), GET_RTX_NAME (ZERO_EXTEND),
		 zext_cost, word_move_cost, word_move_zero_cost);

      if (FORCE_LOWERING || zext_cost >= word_move_cost + word_move_zero_cost)
	choices[speed_p].splitting_zext = true;

      compute_splitting_shift (speed_p, rtxes,
			       choices[speed_p].splitting_ashift, ASHIFT,
			       word_move_zero_cost, word_move_cost);
      compute_splitting_shift (speed_p, rtxes,
			       choices[speed_p].splitting_lshiftrt, LSHIFTRT,
			       word_move_zero_cost, word_move_cost);
      compute_splitting_shift (speed_p, rtxes,
			       choices[speed_p].splitting_ashiftrt, ASHIFTRT,
			       word_move_zero_cost, word_move_cost);
    }
}

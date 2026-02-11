peel_loops_completely (int flags)
{
  struct loop *loop;
  loop_iterator li;
  bool changed = false;


  FOR_EACH_LOOP (li, loop, LI_FROM_INNERMOST)
    {
      loop->lpt_decision.decision = LPT_NONE;
      location_t locus = get_loop_location (loop);

      if (dump_enabled_p ())
	dump_printf_loc (TDF_RTL, locus,
                         ";; *** Considering loop %d at BB %d for "
                         "complete peeling ***\n",
                         loop->num, loop->header->index);

      loop->ninsns = num_loop_insns (loop);

      decide_peel_once_rolling (loop, flags);
      if (loop->lpt_decision.decision == LPT_NONE)
	decide_peel_completely (loop, flags);

      if (loop->lpt_decision.decision == LPT_PEEL_COMPLETELY)
	{
	  report_unroll_peel (loop, locus);
	  peel_loop_completely (loop);
	  changed = true;
	}
    }

    if (changed)
      {
	calculate_dominance_info (CDI_DOMINATORS);
	fix_loop_structure (NULL);
      }
}

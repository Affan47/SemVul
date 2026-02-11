flow_find_cross_jump (basic_block bb1, basic_block bb2, rtx *f1, rtx *f2)
{
  rtx i1, i2, last1, last2, afterlast1, afterlast2;
  int ninsns = 0;


  i1 = BB_END (bb1);
  last1 = afterlast1 = last2 = afterlast2 = NULL_RTX;
  if (onlyjump_p (i1)
      || (returnjump_p (i1) && !side_effects_p (PATTERN (i1))))
    {
      last1 = i1;
      i1 = PREV_INSN (i1);
    }

  i2 = BB_END (bb2);
  if (onlyjump_p (i2)
      || (returnjump_p (i2) && !side_effects_p (PATTERN (i2))))
    {
      last2 = i2;

      if (!simplejump_p (i2) && !returnjump_p (i2) && last1)
	ninsns++;
      i2 = PREV_INSN (i2);
    }

  while (true)
    {

      while (!NONDEBUG_INSN_P (i1) && i1 != BB_HEAD (bb1))
	i1 = PREV_INSN (i1);

      while (!NONDEBUG_INSN_P (i2) && i2 != BB_HEAD (bb2))
	i2 = PREV_INSN (i2);

      if (i1 == BB_HEAD (bb1) || i2 == BB_HEAD (bb2))
	break;

      if (!old_insns_match_p (0, i1, i2))
	break;

      merge_memattrs (i1, i2);


      if (INSN_P (i1))
	{
	  merge_notes (i1, i2);

	  afterlast1 = last1, afterlast2 = last2;
	  last1 = i1, last2 = i2;
	  ninsns++;
	}

      i1 = PREV_INSN (i1);
      i2 = PREV_INSN (i2);
    }

#ifdef HAVE_cc0


  if (ninsns && reg_mentioned_p (cc0_rtx, last1) && ! sets_cc0_p (last1))
    last1 = afterlast1, last2 = afterlast2, ninsns--;
#endif


  if (ninsns)
    {
      while (last1 != BB_HEAD (bb1) && !NONDEBUG_INSN_P (PREV_INSN (last1)))
	last1 = PREV_INSN (last1);

      if (last1 != BB_HEAD (bb1) && LABEL_P (PREV_INSN (last1)))
	last1 = PREV_INSN (last1);

      while (last2 != BB_HEAD (bb2) && !NONDEBUG_INSN_P (PREV_INSN (last2)))
	last2 = PREV_INSN (last2);

      if (last2 != BB_HEAD (bb2) && LABEL_P (PREV_INSN (last2)))
	last2 = PREV_INSN (last2);

      *f1 = last1;
      *f2 = last2;
    }

  return ninsns;
}

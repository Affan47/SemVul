cheap_bb_rtx_cost_p (const_basic_block bb, int scale, int max_cost)
{
  int count = 0;
  rtx insn = BB_HEAD (bb);
  bool speed = optimize_bb_for_speed_p (bb);


  scale += REG_BR_PROB_BASE / 8;
  max_cost *= scale;

  while (1)
    {
      if (NONJUMP_INSN_P (insn))
	{
	  int cost = insn_rtx_cost (PATTERN (insn), speed) * REG_BR_PROB_BASE;
	  if (cost == 0)
	    return false;


#ifdef STACK_REGS
	  {
	    rtx set = single_set (insn);
	    if (set && STACK_REG_P (SET_DEST (set)))
	      return false;
	  }
#endif

	  count += cost;
	  if (count >= max_cost)
	    return false;
	}
      else if (CALL_P (insn))
	return false;

      if (insn == BB_END (bb))
	break;
      insn = NEXT_INSN (insn);
    }

  return true;
}

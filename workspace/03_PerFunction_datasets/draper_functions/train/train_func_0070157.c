rgn_rank (rtx insn1, rtx insn2)
{

  if (INSN_BB (insn1) != INSN_BB (insn2))
    {
      int spec_val, prob_val;


      if ((INSN_BB (insn2) == target_bb) && (INSN_BB (insn1) != target_bb))
	return 1;
      if ((INSN_BB (insn1) == target_bb) && (INSN_BB (insn2) != target_bb))
	return -1;


      spec_val = IS_SPECULATIVE_INSN (insn1) - IS_SPECULATIVE_INSN (insn2);
      if (spec_val)
	return spec_val;


      prob_val = INSN_PROBABILITY (insn2) - INSN_PROBABILITY (insn1);
      if (prob_val)
	return prob_val;
    }
  return 0;
}

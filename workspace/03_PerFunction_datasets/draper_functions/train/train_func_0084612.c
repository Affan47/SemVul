cfg_layout_can_duplicate_bb_p (const_basic_block bb)
{


  if (tablejump_p (BB_END (bb), NULL, NULL))
    return false;


  if (targetm.cannot_copy_insn_p)
    {
      rtx insn = BB_HEAD (bb);
      while (1)
	{
	  if (INSN_P (insn) && targetm.cannot_copy_insn_p (insn))
	    return false;
	  if (insn == BB_END (bb))
	    break;
	  insn = NEXT_INSN (insn);
	}
    }

  return true;
}

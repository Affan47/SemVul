purge_reg_equiv_notes (void)
{
  rtx insn;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      while (1)
	{
	  rtx note = find_reg_note (insn, REG_EQUIV, 0);
	  if (note)
	    {


	      remove_note (insn, note);
	      continue;
	    }
	  break;
	}
    }
}

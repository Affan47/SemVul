find_label_refs (f, lvl)
     rtx f;
     rtx lvl;
{
  rtx insn;

  for (insn = f; insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && GET_CODE (insn) != JUMP_INSN)
      {
	rtx note;


	for (note = REG_NOTES (insn); note; note = XEXP (note, 1))
	  if (REG_NOTE_KIND (note) == REG_LABEL)
	    {
	      rtx lab = XEXP (note, 0), next;

	      if ((next = next_nonnote_insn (lab)) != NULL
		  && GET_CODE (next) == JUMP_INSN
		  && (GET_CODE (PATTERN (next)) == ADDR_VEC
		      || GET_CODE (PATTERN (next)) == ADDR_DIFF_VEC))
		;
	      else if (GET_CODE (lab) == NOTE)
		;
	      else if (GET_CODE (NEXT_INSN (insn)) == JUMP_INSN
		       && find_reg_note (NEXT_INSN (insn), REG_LABEL, lab))
		;
	      else
		lvl = alloc_EXPR_LIST (0, XEXP (note, 0), lvl);
	    }
      }

  return lvl;
}

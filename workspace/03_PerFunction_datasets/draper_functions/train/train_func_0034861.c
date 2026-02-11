delete_computation (rtx insn)
{
  rtx note, next;

#ifdef HAVE_cc0
  if (reg_referenced_p (cc0_rtx, PATTERN (insn)))
    {
      rtx prev = prev_nonnote_insn (insn);


      if (prev && GET_CODE (prev) == INSN
	  && sets_cc0_p (PATTERN (prev)))
	{
	  if (sets_cc0_p (PATTERN (prev)) > 0
	      && ! side_effects_p (PATTERN (prev)))
	    delete_computation (prev);
	  else

	    REG_NOTES (prev) = gen_rtx_EXPR_LIST (REG_UNUSED,
						  cc0_rtx, REG_NOTES (prev));
	}
    }
#endif

  for (note = REG_NOTES (insn); note; note = next)
    {
      next = XEXP (note, 1);

      if (REG_NOTE_KIND (note) != REG_DEAD

	  || GET_CODE (XEXP (note, 0)) != REG)
	continue;

      delete_prior_computation (note, insn);
    }

  delete_related_insns (insn);
}

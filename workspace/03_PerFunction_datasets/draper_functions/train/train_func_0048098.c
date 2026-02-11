propagate_block_delete_insn (rtx insn)
{
  rtx inote = find_reg_note (insn, REG_LABEL, NULL_RTX);


  if (inote && GET_CODE (inote) == CODE_LABEL)
    {
      rtx label = XEXP (inote, 0);
      rtx next;


      if (LABEL_NUSES (label) == 1 + LABEL_PRESERVE_P (label)
	  && (next = next_nonnote_insn (label)) != NULL
	  && GET_CODE (next) == JUMP_INSN
	  && (GET_CODE (PATTERN (next)) == ADDR_VEC
	      || GET_CODE (PATTERN (next)) == ADDR_DIFF_VEC))
	{
	  rtx pat = PATTERN (next);
	  int diff_vec_p = GET_CODE (pat) == ADDR_DIFF_VEC;
	  int len = XVECLEN (pat, diff_vec_p);
	  int i;

	  for (i = 0; i < len; i++)
	    LABEL_NUSES (XEXP (XVECEXP (pat, diff_vec_p, i), 0))--;

	  delete_insn_and_edges (next);
	  ndead++;
	}
    }

  delete_insn_and_edges (insn);
  ndead++;
}

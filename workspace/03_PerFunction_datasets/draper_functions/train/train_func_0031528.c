scope_to_insns_finalize ()
{
  tree cur_block = DECL_INITIAL (cfun->decl);
  rtx insn, note;

  insn = get_insns ();
  if (!active_insn_p (insn))
    insn = next_active_insn (insn);
  for (; insn; insn = next_active_insn (insn))
    {
      tree this_block;

      this_block = INSN_SCOPE (insn);


      if (GET_CODE (PATTERN (insn)) == SEQUENCE)
	{
	  int i;
	  rtx body = PATTERN (insn);

	  this_block = NULL;
	  for (i = 0; i < XVECLEN (body, 0); i++)
	    this_block = choose_inner_scope (this_block,
			    		 INSN_SCOPE (XVECEXP (body, 0, i)));
	}
      if (! this_block)
	continue;

      if (this_block != cur_block)
	{
	  change_scope (insn, cur_block, this_block);
	  cur_block = this_block;
	}
    }


  note = emit_note (NULL, NOTE_INSN_DELETED);
  change_scope (note, cur_block, DECL_INITIAL (cfun->decl));
  delete_insn (note);

  reorder_blocks ();
}

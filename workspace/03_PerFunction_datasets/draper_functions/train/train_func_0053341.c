try_copy_prop (const struct loop *loop, rtx replacement, unsigned int regno)
{

  rtx reg_rtx = regno_reg_rtx[regno];
  rtx init_insn = 0;
  rtx insn;

  int replaced_last = 0;
  int store_is_first = 0;

  for (insn = next_insn_in_loop (loop, loop->scan_start);
       insn != NULL_RTX;
       insn = next_insn_in_loop (loop, insn))
    {
      rtx set;


      if (GET_CODE (insn) == CODE_LABEL && init_insn)
	break;

      if (! INSN_P (insn))
	continue;


      set = single_set (insn);
      if (set
	  && GET_CODE (SET_DEST (set)) == REG
	  && REGNO (SET_DEST (set)) == regno)
	{
	  if (init_insn)
	    abort ();

	  init_insn = insn;
	  if (REGNO_FIRST_UID (regno) == INSN_UID (insn))
	    store_is_first = 1;
	}


      if (init_insn && insn != init_insn)
	{
	  struct note_reg_stored_arg arg;

	  replace_loop_regs (insn, reg_rtx, replacement);
	  if (REGNO_LAST_UID (regno) == INSN_UID (insn))
	    replaced_last = 1;


	  arg.reg = replacement;
	  arg.set_seen = 0;
	  note_stores (PATTERN (insn), note_reg_stored, &arg);
	  if (arg.set_seen)
	    {
	      rtx note = find_reg_note (insn, REG_EQUAL, NULL);


	      if (note && reg_mentioned_p (replacement, XEXP (note, 0)))
		remove_note (insn, note);
	      break;
	    }
	}
    }
  if (! init_insn)
    abort ();
  if (apply_change_group ())
    {
      if (loop_dump_stream)
	fprintf (loop_dump_stream, "  Replaced reg %d", regno);
      if (store_is_first && replaced_last)
	{
	  rtx first;
	  rtx retval_note;


	  first = init_insn;


	  retval_note = find_reg_note (init_insn, REG_RETVAL, NULL_RTX);


	  if (retval_note)
	    first = XEXP (retval_note, 0);


	  loop_delete_insns (first, init_insn);
	}
      if (loop_dump_stream)
	fprintf (loop_dump_stream, ".\n");
    }
}

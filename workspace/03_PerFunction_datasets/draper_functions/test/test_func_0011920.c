never_reached_warning (avoided_insn, finish)
     rtx avoided_insn, finish;
{
  rtx insn;
  rtx a_line_note = NULL;
  int two_avoided_lines = 0, contains_insn = 0, reached_end = 0;

  if (!warn_notreached)
    return;


  insn = avoided_insn;
  while (1)
    {
      rtx prev = PREV_INSN (insn);
      if (prev == NULL_RTX
	  || GET_CODE (prev) != NOTE)
	break;
      insn = prev;
    }


  for (; insn != NULL; insn = NEXT_INSN (insn))
    {
      if ((finish == NULL && GET_CODE (insn) == CODE_LABEL)
	  || GET_CODE (insn) == BARRIER)
	break;

      if (GET_CODE (insn) == NOTE
	  && NOTE_LINE_NUMBER (insn) >= 0)
	{
	  if (a_line_note == NULL)
	    a_line_note = insn;
	  else
	    two_avoided_lines |= (NOTE_LINE_NUMBER (a_line_note)
				  != NOTE_LINE_NUMBER (insn));
	}
      else if (INSN_P (insn))
	{
	  if (reached_end)
	    break;
	  contains_insn = 1;
	}

      if (insn == finish)
	reached_end = 1;
    }
  if (two_avoided_lines && contains_insn)
    warning_with_file_and_line (NOTE_SOURCE_FILE (a_line_note),
				NOTE_LINE_NUMBER (a_line_note),
				"will never be executed");
}

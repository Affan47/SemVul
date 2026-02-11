before_next_cfi_note (rtx start)
{
  rtx prev = start;
  while (start)
    {
      if (NOTE_P (start) && NOTE_KIND (start) == NOTE_INSN_CFI)
	return prev;
      prev = start;
      start = NEXT_INSN (start);
    }
  gcc_unreachable ();
}

find_reg_note (insn, kind, datum)
     rtx insn;
     enum reg_note kind;
     rtx datum;
{
  rtx link;


  if (! INSN_P (insn))
    return 0;

  for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
    if (REG_NOTE_KIND (link) == kind
	&& (datum == 0 || datum == XEXP (link, 0)))
      return link;
  return 0;
}

dwarf2out_frame_debug_def_cfa (rtx pat, const char *label)
{
  memset (&cfa, 0, sizeof (cfa));

  switch (GET_CODE (pat))
    {
    case PLUS:
      cfa.reg = REGNO (XEXP (pat, 0));
      cfa.offset = INTVAL (XEXP (pat, 1));
      break;

    case REG:
      cfa.reg = REGNO (pat);
      break;

    case MEM:
      cfa.indirect = 1;
      pat = XEXP (pat, 0);
      if (GET_CODE (pat) == PLUS)
	{
	  cfa.base_offset = INTVAL (XEXP (pat, 1));
	  pat = XEXP (pat, 0);
	}
      cfa.reg = REGNO (pat);
      break;

    default:

      gcc_unreachable ();
    }

  def_cfa_1 (label, &cfa);
}

dwarf2out_frame_debug_cfa_register (rtx set, const char *label)
{
  rtx src, dest;
  unsigned sregno, dregno;

  src = XEXP (set, 1);
  dest = XEXP (set, 0);

  if (src == pc_rtx)
    sregno = DWARF_FRAME_RETURN_COLUMN;
  else
    sregno = DWARF_FRAME_REGNUM (REGNO (src));

  dregno = DWARF_FRAME_REGNUM (REGNO (dest));


  reg_save (label, sregno, dregno, 0);
}

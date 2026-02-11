subreg_regno_offset (unsigned int xregno, enum machine_mode xmode,
		     unsigned int offset, enum machine_mode ymode)
{
  int nregs_xmode, nregs_ymode;
  int mode_multiple, nregs_multiple;
  int y_offset;

  if (xregno >= FIRST_PSEUDO_REGISTER)
    abort ();

  nregs_xmode = HARD_REGNO_NREGS (xregno, xmode);
  nregs_ymode = HARD_REGNO_NREGS (xregno, ymode);


  if (offset == 0
      && nregs_ymode > nregs_xmode
      && (GET_MODE_SIZE (ymode) > UNITS_PER_WORD
	  ? WORDS_BIG_ENDIAN : BYTES_BIG_ENDIAN))
    return nregs_xmode - nregs_ymode;

  if (offset == 0 || nregs_xmode == nregs_ymode)
    return 0;


  mode_multiple = GET_MODE_SIZE (xmode) / GET_MODE_SIZE (ymode);
  if (mode_multiple == 0)
    abort ();

  y_offset = offset / GET_MODE_SIZE (ymode);
  nregs_multiple =  nregs_xmode / nregs_ymode;
  return (y_offset / (mode_multiple / nregs_multiple)) * nregs_ymode;
}

maybe_mode_change (orig_mode, copy_mode, new_mode, regno, copy_regno)
     enum machine_mode orig_mode, copy_mode, new_mode;
     unsigned int regno, copy_regno;
{
  if (orig_mode == new_mode)
    return gen_rtx_raw_REG (new_mode, regno);
  else if (mode_change_ok (orig_mode, new_mode, regno))
    {
      int copy_nregs = HARD_REGNO_NREGS (copy_regno, copy_mode);
      int use_nregs = HARD_REGNO_NREGS (copy_regno, new_mode);
      int copy_offset
	= GET_MODE_SIZE (copy_mode) / copy_nregs * (copy_nregs - use_nregs);
      int offset
	= GET_MODE_SIZE (orig_mode) - GET_MODE_SIZE (new_mode) - copy_offset;
      int byteoffset = offset % UNITS_PER_WORD;
      int wordoffset = offset - byteoffset;

      offset = ((WORDS_BIG_ENDIAN ? wordoffset : 0)
		+ (BYTES_BIG_ENDIAN ? byteoffset : 0));
      return gen_rtx_raw_REG (new_mode,
			      regno + subreg_regno_offset (regno, orig_mode,
							   offset,
							   new_mode));
    }
  return NULL_RTX;
}

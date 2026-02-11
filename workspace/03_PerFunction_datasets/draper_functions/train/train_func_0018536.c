rtx_to_bits (rtx x)
{
  unsigned int len, beg;
  len = GET_MODE_SIZE (GET_MODE (x));
  beg = (GET_CODE (x) == SUBREG) ? SUBREG_BYTE (x) : 0;
  return BL_TO_WORD (beg, len);
}

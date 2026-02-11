xlib_get_prec_from_mask(unsigned long val)
{
  unsigned long retval = 0;
  unsigned int cur_bit = 0;


  while (cur_bit < (sizeof(unsigned long) * 8)) {
    if ((val >> cur_bit) & 0x1) {
      retval++;
    }
    cur_bit++;
  }
  return retval;
}

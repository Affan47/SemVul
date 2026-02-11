final_addr_vec_align (rtx addr_vec)
{
  int align = GET_MODE_SIZE (GET_MODE (PATTERN (addr_vec)));

  if (align > BIGGEST_ALIGNMENT / BITS_PER_UNIT)
    align = BIGGEST_ALIGNMENT / BITS_PER_UNIT;
  return exact_log2 (align);

}

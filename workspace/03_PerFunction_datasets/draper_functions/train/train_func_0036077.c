offsettable_address_p (strictp, mode, y)
     int strictp;
     enum machine_mode mode;
     rtx y;
{
  enum rtx_code ycode = GET_CODE (y);
  rtx z;
  rtx y1 = y;
  rtx *y2;
  int (*addressp) PARAMS ((enum machine_mode, rtx)) =
    (strictp ? strict_memory_address_p : memory_address_p);
  unsigned int mode_sz = GET_MODE_SIZE (mode);

  if (CONSTANT_ADDRESS_P (y))
    return 1;


  if (mode_dependent_address_p (y))
    return 0;


  if (mode_sz == 0)
    mode_sz = BIGGEST_ALIGNMENT / BITS_PER_UNIT;


  if ((ycode == PLUS) && (y2 = find_constant_term_loc (&y1)))
    {
      int good;

      y1 = *y2;
      *y2 = plus_constant (*y2, mode_sz - 1);


      good = (*addressp) (QImode, y);


      *y2 = y1;
      return good;
    }

  if (GET_RTX_CLASS (ycode) == 'a')
    return 0;


  if (GET_CODE (y) == LO_SUM
      && mode != BLKmode
      && mode_sz <= GET_MODE_ALIGNMENT (mode) / BITS_PER_UNIT)
    z = gen_rtx_LO_SUM (GET_MODE (y), XEXP (y, 0),
			plus_constant (XEXP (y, 1), mode_sz - 1));
  else
    z = plus_constant (y, mode_sz - 1);


  return (*addressp) (QImode, z);
}

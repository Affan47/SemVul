__round (double x)
{
  int32_t i0, j0;
  u_int32_t i1;

  EXTRACT_WORDS (i0, i1, x);
  j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
  if (j0 < 20)
    {
      if (j0 < 0)
	{
	  math_force_eval (huge + x);

	  i0 &= 0x80000000;
	  if (j0 == -1)
	    i0 |= 0x3ff00000;
	  i1 = 0;
	}
      else
	{
	  u_int32_t i = 0x000fffff >> j0;
	  if (((i0 & i) | i1) == 0)

	    return x;
	  math_force_eval (huge + x);


	  i0 += 0x00080000 >> j0;
	  i0 &= ~i;
	  i1 = 0;
	}
    }
  else if (j0 > 51)
    {
      if (j0 == 0x400)

	return x + x;
      else
	return x;
    }
  else
    {
      u_int32_t i = 0xffffffff >> (j0 - 20);
      if ((i1 & i) == 0)

	return x;

      math_force_eval (huge + x);


      u_int32_t j = i1 + (1 << (51 - j0));
      if (j < i1)
	i0 += 1;
      i1 = j;
      i1 &= ~i;
    }

  INSERT_WORDS (x, i0, i1);
  return x;
}

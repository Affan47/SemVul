gen_lowpart_for_combine (enum machine_mode omode, rtx x)
{
  enum machine_mode imode = GET_MODE (x);
  unsigned int osize = GET_MODE_SIZE (omode);
  unsigned int isize = GET_MODE_SIZE (imode);
  rtx result;

  if (omode == imode)
    return x;


  if (GET_MODE_SIZE (omode) > UNITS_PER_WORD
      && ! (CONST_SCALAR_INT_P (x) || isize == osize))
    goto fail;


  if (GET_CODE (x) == SUBREG && MEM_P (SUBREG_REG (x)))
    {
      x = SUBREG_REG (x);


      imode = GET_MODE (x);

      if (imode == omode)
	return x;

      isize = GET_MODE_SIZE (imode);
    }

  result = gen_lowpart_common (omode, x);

  if (result)
    return result;

  if (MEM_P (x))
    {
      int offset = 0;


      if (MEM_VOLATILE_P (x)
	  || mode_dependent_address_p (XEXP (x, 0), MEM_ADDR_SPACE (x)))
	goto fail;


      if (isize < osize)
	return gen_rtx_SUBREG (omode, x, 0);

      if (WORDS_BIG_ENDIAN)
	offset = MAX (isize, UNITS_PER_WORD) - MAX (osize, UNITS_PER_WORD);


      if (BYTES_BIG_ENDIAN)
	offset -= MIN (UNITS_PER_WORD, osize) - MIN (UNITS_PER_WORD, isize);

      return adjust_address_nv (x, omode, offset);
    }


  else if (COMPARISON_P (x))
    return gen_rtx_fmt_ee (GET_CODE (x), omode, XEXP (x, 0), XEXP (x, 1));


  else
    {
      int offset = 0;
      rtx res;

      offset = subreg_lowpart_offset (omode, imode);
      if (imode == VOIDmode)
	{
	  imode = int_mode_for_mode (omode);
	  x = gen_lowpart_common (imode, x);
	  if (x == NULL)
	    goto fail;
	}
      res = simplify_gen_subreg (omode, x, imode, offset);
      if (res)
	return res;
    }

 fail:
  return gen_rtx_CLOBBER (omode, const0_rtx);
}

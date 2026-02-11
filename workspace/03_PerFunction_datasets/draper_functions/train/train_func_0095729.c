extract_split_bit_field (rtx op0, unsigned HOST_WIDE_INT bitsize,
			 unsigned HOST_WIDE_INT bitpos, int unsignedp)
{
  unsigned int unit;
  unsigned int bitsdone = 0;
  rtx result = NULL_RTX;
  int first = 1;


  if (REG_P (op0) || GET_CODE (op0) == SUBREG)
    unit = BITS_PER_WORD;
  else
    unit = MIN (MEM_ALIGN (op0), BITS_PER_WORD);

  while (bitsdone < bitsize)
    {
      unsigned HOST_WIDE_INT thissize;
      rtx part, word;
      unsigned HOST_WIDE_INT thispos;
      unsigned HOST_WIDE_INT offset;

      offset = (bitpos + bitsdone) / unit;
      thispos = (bitpos + bitsdone) % unit;


      thissize = MIN (bitsize - bitsdone, BITS_PER_WORD);
      thissize = MIN (thissize, unit - thispos);


      if (GET_CODE (op0) == SUBREG)
	{
	  int word_offset = (SUBREG_BYTE (op0) / UNITS_PER_WORD) + offset;
	  word = operand_subword_force (SUBREG_REG (op0), word_offset,
					GET_MODE (SUBREG_REG (op0)));
	  offset = 0;
	}
      else if (REG_P (op0))
	{
	  word = operand_subword_force (op0, offset, GET_MODE (op0));
	  offset = 0;
	}
      else
	word = op0;


      part = extract_fixed_bit_field (word_mode, word,
				      offset * unit / BITS_PER_UNIT,
				      thissize, thispos, 0, 1, false);
      bitsdone += thissize;


      if (BYTES_BIG_ENDIAN)
	{
	  if (bitsize != bitsdone)
	    part = expand_shift (LSHIFT_EXPR, word_mode, part,
				 bitsize - bitsdone, 0, 1);
	}
      else
	{
	  if (bitsdone != thissize)
	    part = expand_shift (LSHIFT_EXPR, word_mode, part,
				 bitsdone - thissize, 0, 1);
	}

      if (first)
	result = part;
      else


	result = expand_binop (word_mode, ior_optab, part, result, NULL_RTX, 1,
			       OPTAB_LIB_WIDEN);

      first = 0;
    }


  if (unsignedp)
    return result;

  result = expand_shift (LSHIFT_EXPR, word_mode, result,
			 BITS_PER_WORD - bitsize, NULL_RTX, 0);
  return expand_shift (RSHIFT_EXPR, word_mode, result,
		       BITS_PER_WORD - bitsize, NULL_RTX, 0);
}

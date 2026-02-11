expand_abs_nojump (enum machine_mode mode, rtx op0, rtx target,
		   int result_unsignedp)
{
  rtx temp;

  if (! flag_trapv)
    result_unsignedp = 1;


  temp = expand_unop (mode, result_unsignedp ? abs_optab : absv_optab,
                      op0, target, 0);
  if (temp != 0)
    return temp;


  if (GET_MODE_CLASS (mode) == MODE_FLOAT
      && GET_MODE_BITSIZE (mode) <= 2 * HOST_BITS_PER_WIDE_INT)
    {
      const struct real_format *fmt = REAL_MODE_FORMAT (mode);
      enum machine_mode imode = int_mode_for_mode (mode);
      int bitpos = (fmt != 0) ? fmt->signbit : -1;

      if (imode != BLKmode && bitpos >= 0)
	{
	  HOST_WIDE_INT hi, lo;
	  rtx last = get_last_insn ();


	  if (FLOAT_WORDS_BIG_ENDIAN != WORDS_BIG_ENDIAN)
	    {
	      int nwords = GET_MODE_BITSIZE (mode) / BITS_PER_WORD;
	      int word = nwords - (bitpos / BITS_PER_WORD) - 1;
	      bitpos = word * BITS_PER_WORD + bitpos % BITS_PER_WORD;
	    }

	  if (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      hi = 0;
	      lo = (HOST_WIDE_INT) 1 << bitpos;
	    }
	  else
	    {
	      hi = (HOST_WIDE_INT) 1 << (bitpos - HOST_BITS_PER_WIDE_INT);
	      lo = 0;
	    }
	  temp = expand_binop (imode, and_optab,
			       gen_lowpart (imode, op0),
			       immed_double_const (~lo, ~hi, imode),
			       NULL_RTX, 1, OPTAB_LIB_WIDEN);
	  if (temp != 0)
	    {
	      rtx insn;
	      if (target == 0)
		target = gen_reg_rtx (mode);
	      insn = emit_move_insn (target, gen_lowpart (mode, temp));
	      set_unique_reg_note (insn, REG_EQUAL,
				   gen_rtx_fmt_e (ABS, mode,
						  copy_rtx (op0)));
	      return target;
	    }
	  delete_insns_since (last);
	}
    }


  if (smax_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
    {
      rtx last = get_last_insn ();

      temp = expand_unop (mode, neg_optab, op0, NULL_RTX, 0);
      if (temp != 0)
	temp = expand_binop (mode, smax_optab, op0, temp, target, 0,
			     OPTAB_WIDEN);

      if (temp != 0)
	return temp;

      delete_insns_since (last);
    }


  if (GET_MODE_CLASS (mode) == MODE_INT && BRANCH_COST >= 2)
    {
      rtx extended = expand_shift (RSHIFT_EXPR, mode, op0,
				   size_int (GET_MODE_BITSIZE (mode) - 1),
				   NULL_RTX, 0);

      temp = expand_binop (mode, xor_optab, extended, op0, target, 0,
			   OPTAB_LIB_WIDEN);
      if (temp != 0)
	temp = expand_binop (mode, result_unsignedp ? sub_optab : subv_optab,
                             temp, extended, target, 0, OPTAB_LIB_WIDEN);

      if (temp != 0)
	return temp;
    }

  return NULL_RTX;
}

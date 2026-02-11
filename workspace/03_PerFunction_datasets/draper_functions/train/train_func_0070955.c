expand_vector_unop (mode, unoptab, op0, target, unsignedp)
     enum machine_mode mode;
     optab unoptab;
     rtx op0;
     rtx target;
     int unsignedp;
{
  enum machine_mode submode, tmode;
  int size, elts, subsize, subbitsize, i;
  rtx t, a, res, seq;

  size = GET_MODE_SIZE (mode);
  submode = GET_MODE_INNER (mode);


  for (tmode = GET_CLASS_NARROWEST_MODE (GET_MODE_CLASS (mode));
       GET_MODE_SIZE (tmode) < GET_MODE_SIZE (mode);
       tmode = GET_MODE_WIDER_MODE (tmode))
    {
      if (GET_MODE_INNER (tmode) == GET_MODE_INNER (mode)
	  && unoptab->handlers[(int) tmode].insn_code != CODE_FOR_nothing)
	submode = tmode;
    }

  if (unoptab == neg_optab && GET_MODE_CLASS (submode) == MODE_INT


      && GET_MODE (op0) == mode)
    {
      rtx temp;
      temp = expand_binop (mode, sub_optab, CONST0_RTX (mode), op0,
                           target, unsignedp, OPTAB_DIRECT);
      if (temp)
	return temp;
    }

  if (unoptab == one_cmpl_optab)
    {
      tmode = int_mode_for_mode (mode);
      if (tmode != BLKmode)
	submode = tmode;
    }

  subsize = GET_MODE_SIZE (submode);
  subbitsize = GET_MODE_BITSIZE (submode);
  elts = size / subsize;


  if (GET_MODE (op0) != mode)
    op0 = copy_to_mode_reg (mode, op0);

  if (!target)
    target = gen_reg_rtx (mode);

  start_sequence ();

  for (i = 0; i < elts; ++i)
    {


      if (GET_CODE (target) == REG
	  && (BYTES_BIG_ENDIAN
	      ?  subsize < UNITS_PER_WORD
	      : ((i * subsize) % UNITS_PER_WORD) != 0))
	t = NULL_RTX;
      else
	t = simplify_gen_subreg (submode, target, mode, i * subsize);
      if (CONSTANT_P (op0))
	a = simplify_gen_subreg (submode, op0, mode, i * subsize);
      else
	a = extract_bit_field (op0, subbitsize, i * subbitsize, unsignedp,
			       t, submode, submode, size);

      res = expand_unop (submode, unoptab, a, t, unsignedp);

      if (t)
	emit_move_insn (t, res);
      else
	store_bit_field (target, subbitsize, i * subbitsize, submode, res,
			 size);
    }

  seq = get_insns ();
  end_sequence ();
  emit_insn (seq);

  return target;
}

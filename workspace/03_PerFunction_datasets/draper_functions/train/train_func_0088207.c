expand_builtin_strlen (tree arglist, rtx target,
		       enum machine_mode target_mode)
{
  if (!validate_arglist (arglist, POINTER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      rtx pat;
      tree len, src = TREE_VALUE (arglist);
      rtx result, src_reg, char_rtx, before_strlen;
      enum machine_mode insn_mode = target_mode, char_mode;
      enum insn_code icode = CODE_FOR_nothing;
      int align;


      len = c_strlen (src, 0);
      if (len)
	return expand_expr (len, target, target_mode, EXPAND_NORMAL);


      len = c_strlen (src, 1);
      if (len && TREE_CODE (len) == INTEGER_CST)
	{
	  expand_expr (src, const0_rtx, VOIDmode, EXPAND_NORMAL);
	  return expand_expr (len, target, target_mode, EXPAND_NORMAL);
	}

      align = get_pointer_alignment (src, BIGGEST_ALIGNMENT) / BITS_PER_UNIT;


      if (align == 0)
	return 0;


      while (insn_mode != VOIDmode)
	{
	  icode = strlen_optab->handlers[(int) insn_mode].insn_code;
	  if (icode != CODE_FOR_nothing)
	    break;

	  insn_mode = GET_MODE_WIDER_MODE (insn_mode);
	}
      if (insn_mode == VOIDmode)
	return 0;


      result = target;
      if (! (result != 0
	     && GET_CODE (result) == REG
	     && GET_MODE (result) == insn_mode
	     && REGNO (result) >= FIRST_PSEUDO_REGISTER))
	result = gen_reg_rtx (insn_mode);


      src_reg = gen_reg_rtx (Pmode);


      before_strlen = get_last_insn ();

      char_rtx = const0_rtx;
      char_mode = insn_data[(int) icode].operand[2].mode;
      if (! (*insn_data[(int) icode].operand[2].predicate) (char_rtx,
							    char_mode))
	char_rtx = copy_to_mode_reg (char_mode, char_rtx);

      pat = GEN_FCN (icode) (result, gen_rtx_MEM (BLKmode, src_reg),
			     char_rtx, GEN_INT (align));
      if (! pat)
	return 0;
      emit_insn (pat);


      start_sequence ();
      pat = memory_address (BLKmode,
			    expand_expr (src, src_reg, ptr_mode, EXPAND_SUM));
      if (pat != src_reg)
	emit_move_insn (src_reg, pat);
      pat = get_insns ();
      end_sequence ();

      if (before_strlen)
	emit_insn_after (pat, before_strlen);
      else
	emit_insn_before (pat, get_insns ());


      if (GET_MODE (result) == target_mode)
	target = result;
      else if (target != 0)
	convert_move (target, result, 0);
      else
	target = convert_to_mode (target_mode, result, 0);

      return target;
    }
}

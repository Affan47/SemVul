insert_var_expansion_initialization (struct var_to_expand *ve,
				     basic_block place)
{
  rtx seq, var, zero_init;
  unsigned i;
  enum machine_mode mode = GET_MODE (ve->reg);
  bool honor_signed_zero_p = HONOR_SIGNED_ZEROS (mode);

  if (ve->var_expansions.length () == 0)
    return;

  start_sequence ();
  switch (ve->op)
    {
    case FMA:

    case PLUS:
    case MINUS:
      FOR_EACH_VEC_ELT (ve->var_expansions, i, var)
        {
	  if (honor_signed_zero_p)
	    zero_init = simplify_gen_unary (NEG, mode, CONST0_RTX (mode), mode);
	  else
	    zero_init = CONST0_RTX (mode);
          emit_move_insn (var, zero_init);
        }
      break;

    case MULT:
      FOR_EACH_VEC_ELT (ve->var_expansions, i, var)
        {
          zero_init = CONST1_RTX (GET_MODE (var));
          emit_move_insn (var, zero_init);
        }
      break;

    default:
      gcc_unreachable ();
    }

  seq = get_insns ();
  end_sequence ();

  emit_insn_after (seq, BB_END (place));
}

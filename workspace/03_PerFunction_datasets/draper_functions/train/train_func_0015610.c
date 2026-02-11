xtensa_expand_atomic (enum rtx_code code, rtx target, rtx mem, rtx val,
		      bool after)
{
  enum machine_mode mode = GET_MODE (mem);
  struct alignment_context ac;
  rtx csloop = gen_label_rtx ();
  rtx cmp, tmp;
  rtx old = gen_reg_rtx (SImode);
  rtx new_rtx = gen_reg_rtx (SImode);
  rtx orig = NULL_RTX;

  init_alignment_context (&ac, mem);


  if (ac.shift != NULL_RTX)
    val = xtensa_expand_mask_and_shift (val, mode, ac.shift);
  switch (code)
    {
    case PLUS:
    case MINUS:
      orig = gen_reg_rtx (SImode);
      convert_move (orig, val, 1);
      break;

    case SET:
    case IOR:
    case XOR:
      break;

    case MULT:
    case AND:

      val = expand_simple_binop (SImode, XOR, val, ac.modemaski,
				 NULL_RTX, 1, OPTAB_DIRECT);
      break;

    default:
      gcc_unreachable ();
    }


  cmp = force_reg (SImode, ac.memsi);

  emit_label (csloop);
  emit_move_insn (old, cmp);

  switch (code)
    {
    case PLUS:
    case MINUS:
      val = expand_simple_binop (SImode, code, old, orig,
				 NULL_RTX, 1, OPTAB_DIRECT);
      val = expand_simple_binop (SImode, AND, val, ac.modemask,
				 NULL_RTX, 1, OPTAB_DIRECT);

    case SET:
      tmp = expand_simple_binop (SImode, AND, old, ac.modemaski,
				 NULL_RTX, 1, OPTAB_DIRECT);
      tmp = expand_simple_binop (SImode, IOR, tmp, val,
				 new_rtx, 1, OPTAB_DIRECT);
      break;

    case AND:
    case IOR:
    case XOR:
      tmp = expand_simple_binop (SImode, code, old, val,
				 new_rtx, 1, OPTAB_DIRECT);
      break;

    case MULT:
      tmp = expand_simple_binop (SImode, XOR, old, ac.modemask,
				 NULL_RTX, 1, OPTAB_DIRECT);
      tmp = expand_simple_binop (SImode, AND, tmp, val,
				 new_rtx, 1, OPTAB_DIRECT);
      break;

    default:
      gcc_unreachable ();
    }

  if (tmp != new_rtx)
    emit_move_insn (new_rtx, tmp);
  emit_insn (gen_sync_compare_and_swapsi (cmp, ac.memsi, old, new_rtx));
  emit_cmp_and_jump_insns (cmp, old, NE, const0_rtx, SImode, true, csloop);

  if (target)
    {
      tmp = (after ? new_rtx : cmp);
      convert_move (target,
		    (ac.shift == NULL_RTX ? tmp
		     : expand_simple_binop (SImode, LSHIFTRT, tmp, ac.shift,
					    NULL_RTX, 1, OPTAB_DIRECT)),
		    1);
    }
}

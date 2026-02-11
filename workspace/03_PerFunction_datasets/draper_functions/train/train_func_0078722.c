stack_protect_epilogue (void)
{
  tree guard_decl = targetm.stack_protect_guard ();
  rtx label = gen_label_rtx ();
  rtx x, y, tmp;

  x = expand_normal (crtl->stack_protect_guard);
  y = expand_normal (guard_decl);


  switch (HAVE_stack_protect_test != 0)
    {
    case 1:
      tmp = gen_stack_protect_test (x, y, label);
      if (tmp)
	{
	  emit_insn (tmp);
	  break;
	}


    default:
      emit_cmp_and_jump_insns (x, y, EQ, NULL_RTX, ptr_mode, 1, label);
      break;
    }


  tmp = get_last_insn ();
  if (JUMP_P (tmp))
    predict_insn_def (tmp, PRED_NORETURN, TAKEN);

  expand_call (targetm.stack_protect_fail (), NULL_RTX, true);
  free_temp_slots ();
  emit_label (label);
}

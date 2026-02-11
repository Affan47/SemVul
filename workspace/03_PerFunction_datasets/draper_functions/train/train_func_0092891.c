emit_stack_restore (enum save_level save_level, rtx sa)
{

  rtx (*fcn) (rtx, rtx) = gen_move_insn;


  if (SUPPORTS_STACK_ALIGNMENT)
    crtl->need_drap = true;


  switch (save_level)
    {
#ifdef HAVE_restore_stack_block
    case SAVE_BLOCK:
      if (HAVE_restore_stack_block)
	fcn = gen_restore_stack_block;
      break;
#endif
#ifdef HAVE_restore_stack_function
    case SAVE_FUNCTION:
      if (HAVE_restore_stack_function)
	fcn = gen_restore_stack_function;
      break;
#endif
#ifdef HAVE_restore_stack_nonlocal
    case SAVE_NONLOCAL:
      if (HAVE_restore_stack_nonlocal)
	fcn = gen_restore_stack_nonlocal;
      break;
#endif
    default:
      break;
    }

  if (sa != 0)
    {
      sa = validize_mem (sa);


      emit_clobber (gen_rtx_MEM (BLKmode, gen_rtx_SCRATCH (VOIDmode)));
      emit_clobber (gen_rtx_MEM (BLKmode, stack_pointer_rtx));
    }

  discard_pending_stack_adjust ();

  emit_insn (fcn (stack_pointer_rtx, sa));
}

get_arg_pointer_save_area (struct function *f)
{
  rtx ret = f->x_arg_pointer_save_area;

  if (! ret)
    {
      ret = assign_stack_local_1 (Pmode, GET_MODE_SIZE (Pmode), 0, f);
      f->x_arg_pointer_save_area = ret;
    }

  if (f == cfun && ! f->arg_pointer_save_area_init)
    {
      rtx seq;


      start_sequence ();
      emit_move_insn (validize_mem (ret), virtual_incoming_args_rtx);
      seq = get_insns ();
      end_sequence ();

      push_topmost_sequence ();
      emit_insn_after (seq, get_insns ());
      pop_topmost_sequence ();
    }

  return ret;
}

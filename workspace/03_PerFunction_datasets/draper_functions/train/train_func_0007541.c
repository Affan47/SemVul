gen_return (void)
{
  rtx _val = 0;
  start_sequence ();
  {
#line 11697 "../../src/gcc/config/i386/i386.md"
{
  if (crtl->args.pops_args)
    {
      rtx popc = GEN_INT (crtl->args.pops_args);
      emit_jump_insn (gen_return_pop_internal (popc));
      DONE;
    }
}
  }
  emit_jump_insn (gen_rtx_RETURN (VOIDmode));
  _val = get_insns ();
  end_sequence ();
  return _val;
}

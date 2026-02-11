arm_compute_static_chain_stack_bytes (void)
{
  unsigned long func_type = arm_current_func_type ();
  int static_chain_stack_bytes = 0;

  if (TARGET_APCS_FRAME && frame_pointer_needed && TARGET_ARM &&
      IS_NESTED (func_type) &&
      df_regs_ever_live_p (3) && crtl->args.pretend_args_size == 0)
    static_chain_stack_bytes = 4;

  return static_chain_stack_bytes;
}

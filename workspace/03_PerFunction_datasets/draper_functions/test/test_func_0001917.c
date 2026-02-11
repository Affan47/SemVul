clear_pending_stack_adjust (void)
{
  if (optimize > 0
      && (! flag_omit_frame_pointer || cfun->calls_alloca)
      && EXIT_IGNORE_STACK)
    discard_pending_stack_adjust ();
}

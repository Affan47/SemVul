_gst_plugin_fault_handler_setup (void)
{
  struct sigaction action;


  if (!gst_segtrap_is_enabled ())
    return;

  if (_gst_plugin_fault_handler_is_setup)
    return;

  _gst_plugin_fault_handler_is_setup = TRUE;

  memset (&action, 0, sizeof (action));
  action.sa_handler = _gst_plugin_fault_handler_sighandler;

  sigaction (SIGSEGV, &action, &oldaction);
}

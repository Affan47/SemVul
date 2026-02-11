main (int argc,
      char **argv)
{
#ifdef ENABLE_DEBUG
  tp_debug_divert_messages (g_getenv ("EXAMPLE_CM_LOGFILE"));
  tp_debug_set_flags (g_getenv ("EXAMPLE_DEBUG"));

  if (g_getenv ("EXAMPLE_TIMING") != NULL)
    g_log_set_default_handler (tp_debug_timestamped_log_handler, NULL);

  if (g_getenv ("EXAMPLE_PERSIST") != NULL)
    tp_debug_set_persistent (TRUE);
#endif

  return tp_run_connection_manager ("telepathy-example-cm-csh",
      VERSION, construct_cm, argc, argv);
}

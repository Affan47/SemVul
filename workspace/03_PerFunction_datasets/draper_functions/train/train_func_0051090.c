_gst_boolean_accumulator (GSignalInvocationHint * ihint,
    GValue * return_accu, const GValue * handler_return, gpointer dummy)
{
  gboolean myboolean;

  myboolean = g_value_get_boolean (handler_return);
  if (!(ihint->run_type & G_SIGNAL_RUN_CLEANUP))
    g_value_set_boolean (return_accu, myboolean);


  return myboolean;
}

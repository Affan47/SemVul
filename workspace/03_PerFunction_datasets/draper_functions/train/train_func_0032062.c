main (int argc, char **argv)
{
  g_test_init (&argc, &argv, NULL);

  main_thread = g_thread_self ();

  dconf_engine_dbus_init_for_testing ();


  if (!g_str_equal (DBUS_BACKEND, "/libdbus-1"))
    g_test_add_func (DBUS_BACKEND "/creation/error", test_creation_error);

  g_test_add_func (DBUS_BACKEND "/sync-call/success", test_sync_call_success);
  g_test_add_func (DBUS_BACKEND "/sync-call/error", test_sync_call_error);
  g_test_add_func (DBUS_BACKEND "/async-call/success", test_async_call_success);
  g_test_add_func (DBUS_BACKEND "/async-call/error", test_async_call_error);
  g_test_add_func (DBUS_BACKEND "/sync-call/during-async", test_sync_during_async);
  g_test_add_func (DBUS_BACKEND "/signal/receipt", test_signal_receipt);

  return g_test_run ();
}

test_async_call_error (void)
{
  DConfEngineCallHandle *handle;
  GError *error = NULL;
  gboolean success;

  handle = (gpointer) g_variant_type_new ("(s)");

  g_mutex_lock (&async_call_queue_lock);
  g_queue_push_tail (&async_call_error_queue, handle);
  g_mutex_unlock (&async_call_queue_lock);

  success = dconf_engine_dbus_call_async_func (G_BUS_TYPE_SESSION,
                                               "org.freedesktop.DBus", "/", "org.freedesktop.DBus", "GetId",
                                               g_variant_new ("(s)", ""), handle, &error);
  g_assert_no_error (error);
  g_assert (success);

  wait_for_queue_to_empty (&async_call_error_queue);
}

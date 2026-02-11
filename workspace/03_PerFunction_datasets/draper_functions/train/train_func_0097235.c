tp_run_connection_manager (const char *prog_name,
                           const char *version,
                           TpBaseConnectionManager *(*construct_cm) (void),
                           int argc,
                           char **argv)
{
  DBusConnection *connection = NULL;
  TpDBusDaemon *bus_daemon = NULL;
  GError *error = NULL;
  int ret = 1;

  add_signal_handlers ();

  g_type_init ();

  g_set_prgname (prog_name);

#ifdef ENABLE_BACKTRACE
  g_log_set_handler ("GLib-GObject",
      G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_ERROR |
      G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION,
      critical_handler, NULL);
  g_log_set_handler ("GLib",
      G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_ERROR |
      G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION,
      critical_handler, NULL);
  g_log_set_handler ("tp-glib",
      G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_ERROR |
      G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION,
      critical_handler, NULL);
  g_log_set_handler (NULL,
      G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_ERROR |
      G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION,
      critical_handler, NULL);
#endif

  mainloop = g_main_loop_new (NULL, FALSE);

  bus_daemon = tp_dbus_daemon_dup (&error);

  if (bus_daemon == NULL)
    {
      WARNING ("%s", error->message);
      g_error_free (error);
      error = NULL;
      goto out;
    }

  manager = construct_cm ();

  g_signal_connect (manager, "new-connection",
      (GCallback) new_connection, NULL);

  g_signal_connect (manager, "no-more-connections",
      (GCallback) no_more_connections, NULL);


  connection = dbus_g_connection_get_connection (
      ((TpProxy *) bus_daemon)->dbus_connection);
  dbus_connection_add_filter (connection, dbus_filter_function, NULL, NULL);
  dbus_connection_set_exit_on_disconnect (connection, FALSE);

  if (!tp_base_connection_manager_register (manager))
    {
      g_object_unref (manager);
      manager = NULL;
      goto out;
    }

  g_debug ("started version %s (telepathy-glib version %s)", version,
      VERSION);

  timeout_id = g_timeout_add (DIE_TIME, kill_connection_manager, NULL);

  g_main_loop_run (mainloop);

  g_message ("Exiting");

  ret = 0;

out:

  if (connection != NULL)
    dbus_connection_remove_filter (connection, dbus_filter_function, NULL);

  if (bus_daemon != NULL)
    g_object_unref (bus_daemon);


  if (timeout_id != 0)
    g_source_remove (timeout_id);

  if (mainloop != NULL)
    g_main_loop_unref (mainloop);

  mainloop = NULL;

  g_assert (manager == NULL);

  return ret;
}

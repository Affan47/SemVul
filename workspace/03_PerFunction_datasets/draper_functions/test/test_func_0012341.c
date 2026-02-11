main(int argc, char ** argv)
{
  if (getenv("HOME") == NULL)
  {
    log_error("Environment variable HOME not set");
    return 1;
  }

  INIT_LIST_HEAD(&g_pairs);

  install_term_signal_handler(SIGTERM, false);
  install_term_signal_handler(SIGINT, true);

  if (!connect_dbus())
  {
    log_error("Failed to connect to D-Bus");
    return 1;
  }

  while (!g_quit)
  {
    dbus_connection_read_write_dispatch(cdbus_g_dbus_connection, 50);
  }

  disconnect_dbus();
  return 0;
}

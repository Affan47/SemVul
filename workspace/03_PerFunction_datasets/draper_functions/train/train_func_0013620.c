tp_tests_create_conn (GType conn_type,
    const gchar *account,
    gboolean connect,
    TpBaseConnection **service_conn,
    TpConnection **client_conn)
{
  TpDBusDaemon *dbus;
  TpSimpleClientFactory *factory;
  gchar *name;
  gchar *conn_path;
  GError *error = NULL;

  g_assert (service_conn != NULL);
  g_assert (client_conn != NULL);

  dbus = tp_tests_dbus_daemon_dup_or_die ();
  factory = (TpSimpleClientFactory *) tp_automatic_client_factory_new (dbus);

  *service_conn = tp_tests_object_new_static_class (
        conn_type,
        "account", account,
        "protocol", "simple",
        NULL);
  g_assert (*service_conn != NULL);

  g_assert (tp_base_connection_register (*service_conn, "simple",
        &name, &conn_path, &error));
  g_assert_no_error (error);

  *client_conn = tp_simple_client_factory_ensure_connection (factory,
      conn_path, NULL, &error);
  g_assert (*client_conn != NULL);
  g_assert_no_error (error);

  if (connect)
    {
      GQuark conn_features[] = { TP_CONNECTION_FEATURE_CONNECTED, 0 };

      tp_cli_connection_call_connect (*client_conn, -1, NULL, NULL, NULL, NULL);
      tp_tests_proxy_run_until_prepared (*client_conn, conn_features);
    }

  g_free (name);
  g_free (conn_path);

  g_object_unref (dbus);
  g_object_unref (factory);
}

test_close_immediately (TestConnection *test,
                        gconstpointer   data)
{
  GIOStream *connection;
  GError *error = NULL;

  connection = start_async_server_and_connect_to_it (test, G_TLS_AUTHENTICATION_NONE, TRUE);
  test->client_connection = g_tls_client_connection_new (connection, test->identity, &error);
  g_assert_no_error (error);
  g_object_unref (connection);


  g_io_stream_close (test->client_connection, NULL, &error);
  g_assert_no_error (error);
}

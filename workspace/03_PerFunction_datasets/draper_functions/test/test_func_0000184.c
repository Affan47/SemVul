test_write_during_handshake (TestConnection *test,
			    gconstpointer   data)
{
  GIOStream *connection;
  GError *error = NULL;
  GMainContext *context;
  GMainLoop *loop;
  GOutputStream *ostream;
  gboolean handshake_complete = FALSE;

  g_test_bug ("697754");

  connection = start_async_server_and_connect_to_it (test, G_TLS_AUTHENTICATION_REQUESTED, TRUE);
  test->client_connection = g_tls_client_connection_new (connection, test->identity, &error);
  g_assert_no_error (error);
  g_object_unref (connection);

  loop = g_main_loop_new (NULL, FALSE);
  g_signal_connect (test->client_connection, "notify::accepted-cas",
                    G_CALLBACK (quit_loop_on_notify), loop);

  context = g_main_context_new ();
  g_main_context_push_thread_default (context);
  g_tls_connection_handshake_async (G_TLS_CONNECTION (test->client_connection),
				    G_PRIORITY_DEFAULT, NULL,
				    handshake_completed, &handshake_complete);
  g_main_context_pop_thread_default (context);


  g_main_loop_run (loop);
  g_main_loop_unref (loop);


  ostream = g_io_stream_get_output_stream (test->client_connection);
  g_output_stream_write (ostream, TEST_DATA, TEST_DATA_LENGTH,
			 G_PRIORITY_DEFAULT, &error);
  g_assert_no_error (error);


  while (!handshake_complete)
    g_main_context_iteration (context, TRUE);
  g_main_context_unref (context);
}

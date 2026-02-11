test_property_change (void)
{
  EmpathyIrcServer *server;

  server = empathy_irc_server_new ("test.localhost", 6667, TRUE);
  g_assert (server != NULL);

  g_object_set (server,
      "address", "test2.localhost",
      "port", 6668,
      "ssl", FALSE,
      NULL);

  check_server (server, "test2.localhost", 6668, FALSE);

  g_object_unref (server);
}

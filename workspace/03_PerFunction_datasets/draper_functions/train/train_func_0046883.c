test_watch_sync (void)
{
  DConfEngine *engine;

  dconf_mock_dbus_sync_call_handler = handle_match_request;

  engine = dconf_engine_new (SRCDIR "/profile/dos", NULL, NULL);

  match_request_type = "AddMatch";
  dconf_engine_watch_sync (engine, "/a/b/c");
  g_assert (got_match_request[G_BUS_TYPE_SESSION]);
  g_assert (got_match_request[G_BUS_TYPE_SYSTEM]);
  got_match_request[G_BUS_TYPE_SESSION] = FALSE;
  got_match_request[G_BUS_TYPE_SYSTEM] = FALSE;

  match_request_type = "RemoveMatch";
  dconf_engine_unwatch_sync (engine, "/a/b/c");
  g_assert (got_match_request[G_BUS_TYPE_SESSION]);
  g_assert (got_match_request[G_BUS_TYPE_SYSTEM]);
  got_match_request[G_BUS_TYPE_SESSION] = FALSE;
  got_match_request[G_BUS_TYPE_SYSTEM] = FALSE;

  dconf_engine_unref (engine);

  dconf_mock_dbus_sync_call_handler = NULL;
  match_request_type = NULL;
}

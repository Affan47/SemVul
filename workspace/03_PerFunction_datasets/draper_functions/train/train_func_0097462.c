test_new (Fixture       *f,
          gconstpointer  data)
{
  g_assert (EVD_IS_WEBSOCKET_CLIENT (f->ws_client));
  g_assert (EVD_IS_TRANSPORT (f->ws_client));

  g_assert (EVD_IS_WEBSOCKET_SERVER (f->ws_server));
  g_assert (EVD_IS_WEB_SERVICE (f->ws_server));
  g_assert (EVD_IS_TRANSPORT (f->ws_server));
}

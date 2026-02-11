peer_is_connected (EvdTransport *transport, EvdPeer *peer)
{
  gpointer peer_data;
  EvdHttpConnection *conn;
  EvdWebsocketState state;

  peer_data = g_object_get_data (G_OBJECT (peer), PEER_DATA_KEY);

  if (peer_data == NULL || ! EVD_IS_HTTP_CONNECTION (peer_data))
    return FALSE;

  conn = EVD_HTTP_CONNECTION (peer_data);
  state = evd_websocket_protocol_get_state (conn);

  return state == EVD_WEBSOCKET_STATE_OPENING ||
    state == EVD_WEBSOCKET_STATE_OPENED ||
    state == EVD_WEBSOCKET_STATE_CLOSING;
}

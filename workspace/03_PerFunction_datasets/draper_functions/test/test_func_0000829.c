on_close_frame_received (EvdWebsocketData *data,
                         guint16           code,
                         const gchar      *reason)
{
  data->close_frame_received = TRUE;

  if (data->state == EVD_WEBSOCKET_STATE_CLOSING)
    {
      finish_close_handshake (data, code, reason);
    }
  else
    {
      evd_websocket_protocol_close (data->conn, code, NULL, NULL);
    }
}

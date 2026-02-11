evd_websocket_protocol_send (EvdHttpConnection  *conn,
                             const gchar        *frame,
                             gsize               frame_len,
                             EvdMessageType      frame_type,
                             GError            **error)
{
  EvdWebsocketData *data;

  g_return_val_if_fail (EVD_IS_HTTP_CONNECTION (conn), FALSE);
  g_return_val_if_fail (frame != NULL, FALSE);

  data = g_object_get_data (G_OBJECT (conn), EVD_WEBSOCKET_DATA_KEY);
  if (data == NULL)
    {
      g_set_error (error,
                   G_IO_ERROR,
                   G_IO_ERROR_NOT_INITIALIZED,
                   "Given HTTP connection doesn't appear to be initialized for Websocket");
      return FALSE;
    }

  if (data->state == EVD_WEBSOCKET_STATE_CLOSING ||
      data->state == EVD_WEBSOCKET_STATE_CLOSED)
    {
      g_set_error (error,
                   G_IO_ERROR,
                   G_IO_ERROR_CLOSED,
                   "Websocket connection is closed");
      return FALSE;
    }

  return send_data_frame (data, frame, frame_len, frame_type, error);
}

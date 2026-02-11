on_connection_read (GObject      *obj,
                    GAsyncResult *res,
                    gpointer      user_data)
{
  EvdWebsocketData *data = user_data;
  EvdHttpConnection *conn;
  GError *error = NULL;
  gssize size;

  conn = data->conn;

  size = g_input_stream_read_finish (G_INPUT_STREAM (obj),
                                     res,
                                     &error);
  if (size < 0)
    {
      if (! g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CLOSED))
        {

          g_print ("Error reading from WebSocket: %s", error->message);

          g_io_stream_close (G_IO_STREAM (data->conn), NULL, NULL);
        }

      g_error_free (error);
    }
  else if (size > 0)
    {
      data->buf_len += size;

      if (data->state != EVD_WEBSOCKET_STATE_CLOSED &&
          process_data (data))
        read_from_connection (data);
    }

  g_object_unref (conn);
}

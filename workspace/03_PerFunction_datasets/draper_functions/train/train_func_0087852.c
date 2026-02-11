evd_reproxy_bridge_write (gpointer user_data)
{
  EvdConnection *conn0 = EVD_CONNECTION (user_data);
  EvdReproxyBridge *bridge;
  GOutputStream *stream;
  gssize out_size;
  GError *error = NULL;

  bridge = g_object_get_data (G_OBJECT (conn0), BRIDGE_DATA_KEY);

  stream = g_io_stream_get_output_stream (G_IO_STREAM (bridge->conn));

  if ( (out_size =
        g_output_stream_write (stream, bridge->buf, bridge->size, NULL, &error)) >= 0)
    {
      if (out_size < bridge->size)
        {
          GInputStream *input_stream;

          input_stream = g_io_stream_get_input_stream (G_IO_STREAM (conn0));

          evd_buffered_input_stream_unread (EVD_BUFFERED_INPUT_STREAM (input_stream),
                                            bridge->buf + out_size,
                                            bridge->size - out_size,
                                            NULL,
                                            &error);
        }
      else
        {
          evd_reproxy_bridge_read (conn0);
        }
    }

  if (error != NULL)
    {
      g_debug ("error: %s", error->message);
      g_error_free (error);
    }

  return FALSE;
}

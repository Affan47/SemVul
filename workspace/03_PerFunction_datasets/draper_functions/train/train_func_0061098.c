free_websocket_connection_data (EvdWebsocketData *data)
{
  g_return_if_fail (data != NULL);

  if (data->user_data != NULL && data->user_data_destroy_notify != NULL)
    data->user_data_destroy_notify (data->user_data);

  if (data->buf != NULL)
    g_string_free (data->buf, TRUE);

  if (data->close_timeout_src_id != 0)
    {
      g_source_remove (data->close_timeout_src_id);
      data->close_timeout_src_id = 0;
      g_object_unref (data->conn);
    }

  g_free (data->close_reason);

  g_slice_free (EvdWebsocketData, data);
}

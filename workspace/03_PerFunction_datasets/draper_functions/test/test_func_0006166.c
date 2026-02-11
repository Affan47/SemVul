gst_multi_fd_sink_get_stats (GstMultiFdSink * sink, int fd)
{
  GstTCPClient *client;
  GValueArray *result = NULL;
  GList *clink;

  CLIENTS_LOCK (sink);
  clink = g_hash_table_lookup (sink->fd_hash, &fd);
  if (clink == NULL)
    goto noclient;

  client = (GstTCPClient *) clink->data;
  if (client != NULL) {
    GValue value = { 0 };
    guint64 interval;

    result = g_value_array_new (7);

    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->bytes_sent);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->connect_time);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    if (client->disconnect_time == 0) {
      GTimeVal nowtv;

      g_get_current_time (&nowtv);

      interval = GST_TIMEVAL_TO_TIME (nowtv) - client->connect_time;
    } else {
      interval = client->disconnect_time - client->connect_time;
    }
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->disconnect_time);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, interval);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->last_activity_time);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->dropped_buffers);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->first_buffer_ts);
    result = g_value_array_append (result, &value);
    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, client->last_buffer_ts);
    result = g_value_array_append (result, &value);
  }

noclient:
  CLIENTS_UNLOCK (sink);


  if (result == NULL) {
    GST_WARNING_OBJECT (sink, "[fd %5d] no client with this found!", fd);
    result = g_value_array_new (0);
  }

  return result;
}

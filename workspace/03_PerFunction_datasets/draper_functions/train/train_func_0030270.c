player_buffering_timeout (gpointer data)
{
  ClutterGstPlayer *player = (ClutterGstPlayer *) data;
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);
  gdouble start_d, stop_d, seconds_buffered;
  gint64 start, stop, left;
  GstState current_state;
  GstElement *element;
  GstQuery *query;
  gboolean res;

  element = priv->download_buffering_element;
  if (element == NULL)
    element = priv->pipeline;


  query = gst_query_new_buffering (GST_FORMAT_PERCENT);
  res = gst_element_query (element, query);

  if (res == FALSE)
    {
      priv->buffering_timeout_id = 0;
      player_clear_download_buffering (player);
      return FALSE;
    }


  gst_query_parse_buffering_stats (query, NULL, NULL, NULL, &left);
  gst_query_parse_buffering_range (query, NULL, &start, &stop, NULL);

  CLUTTER_GST_NOTE (BUFFERING,
                    "start %" G_GINT64_FORMAT ", stop %" G_GINT64_FORMAT
                    ", buffering left %" G_GINT64_FORMAT, start, stop, left);

  start_d = (gdouble) start / GST_FORMAT_PERCENT_MAX;
  stop_d = (gdouble) stop / GST_FORMAT_PERCENT_MAX;

  g_signal_emit (player, signals[DOWNLOAD_BUFFERING], 0, start_d, stop_d);


  seconds_buffered = priv->duration * (stop_d - start_d);
  priv->buffer_fill = seconds_buffered / 2.0;
  priv->buffer_fill = CLAMP (priv->buffer_fill, 0.0, 1.0);

  if (priv->buffer_fill != 1.0 || !priv->virtual_stream_buffer_signalled)
    {
      CLUTTER_GST_NOTE (BUFFERING, "buffer holds %0.2fs of data, buffer-fill "
                        "is %.02f", seconds_buffered, priv->buffer_fill);

      g_object_notify (G_OBJECT (player), "buffer-fill");

      if (priv->buffer_fill == 1.0)
        priv->virtual_stream_buffer_signalled = 1;
    }

  gst_element_get_state (priv->pipeline, &current_state, NULL, 0);
  if (priv->buffer_fill < 1.0)
    {
      if (current_state != GST_STATE_PAUSED)
        {
          CLUTTER_GST_NOTE (BUFFERING, "pausing the pipeline");
          gst_element_set_state (priv->pipeline, GST_STATE_PAUSED);
        }
    }
  else
    {
      if (current_state != priv->target_state)
        {
          CLUTTER_GST_NOTE (BUFFERING, "restoring the pipeline");
          gst_element_set_state (priv->pipeline, priv->target_state);
        }
    }


  if (left == G_GINT64_CONSTANT (0))
    {
      priv->buffering_timeout_id = 0;

      player_clear_download_buffering (player);
      gst_query_unref (query);
      return FALSE;
    }

  gst_query_unref (query);
  return TRUE;
}

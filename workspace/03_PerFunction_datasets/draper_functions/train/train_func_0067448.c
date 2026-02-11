gst_base_parse_finalize (GObject * object)
{
  GstBaseParse *parse = GST_BASE_PARSE (object);
  GstEvent **p_ev;

  g_object_unref (parse->priv->adapter);

  if (parse->priv->pending_segment) {
    p_ev = &parse->priv->pending_segment;
    gst_event_replace (p_ev, NULL);
  }
  if (parse->priv->close_segment) {
    p_ev = &parse->priv->close_segment;
    gst_event_replace (p_ev, NULL);
  }

  if (parse->priv->cache) {
    gst_buffer_unref (parse->priv->cache);
    parse->priv->cache = NULL;
  }

  g_list_foreach (parse->priv->pending_events, (GFunc) gst_mini_object_unref,
      NULL);
  g_list_free (parse->priv->pending_events);
  parse->priv->pending_events = NULL;

  g_queue_foreach (&parse->priv->queued_frames,
      (GFunc) gst_base_parse_frame_free, NULL);
  g_queue_clear (&parse->priv->queued_frames);

  if (parse->priv->index) {
    gst_object_unref (parse->priv->index);
    parse->priv->index = NULL;
  }
#if !GLIB_CHECK_VERSION (2, 31, 0)
  g_static_mutex_free (&parse->priv->index_lock);
#else
  g_mutex_clear (&parse->priv->index_lock);
#endif

  gst_base_parse_clear_queues (parse);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

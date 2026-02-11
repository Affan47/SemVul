fs_raw_session_update_direction (FsRawSession *self,
  FsStreamDirection direction)
{
  GError *error = NULL;
  FsRawConference *conference;

  conference = fs_raw_session_get_conference (self, &error);

  if (!conference)
  {
    fs_session_emit_error (FS_SESSION (self), error->code, error->message);
    g_clear_error (&error);
    return;
  }

  GST_OBJECT_LOCK (conference);


  if (!self->priv->codecs)
  {
    GST_OBJECT_UNLOCK (conference);
    goto out;
  }

  if (self->priv->transmitter &&
      !self->priv->transmitter_sink_added &&
      direction & FS_DIRECTION_SEND)  {
    GstElement *transmitter_sink;

    GST_OBJECT_UNLOCK (conference);

    g_object_get (self->priv->transmitter, "gst-sink", &transmitter_sink, NULL);
    if (!transmitter_sink)
    {
      fs_session_emit_error (FS_SESSION (self), FS_ERROR_CONSTRUCTION,
          "Unable to get the sink element from the FsTransmitter");
      goto out;
    }

    if (!_add_transmitter_sink (self, transmitter_sink, &error))
    {
      gst_object_unref (transmitter_sink);
      fs_session_emit_error (FS_SESSION (self), error->code, error->message);
      g_clear_error (&error);
      goto out;
    }

    gst_object_unref (transmitter_sink);

    GST_OBJECT_LOCK (conference);
    self->priv->transmitter_sink_added = TRUE;
  }

  if (self->priv->recv_valve)
  {
    GstElement *valve = g_object_ref (self->priv->recv_valve);

    GST_OBJECT_UNLOCK (conference);
    g_object_set (valve,
        "drop", ! (direction & FS_DIRECTION_RECV), NULL);
    g_object_unref (valve);
    GST_OBJECT_LOCK (conference);
  }

  GST_OBJECT_UNLOCK (conference);

  if (direction & FS_DIRECTION_SEND)
    g_object_set (self->priv->send_valve, "drop", FALSE, NULL);
  else
    g_object_set (self->priv->send_valve, "drop", TRUE, NULL);

out:
  gst_object_unref (conference);
}

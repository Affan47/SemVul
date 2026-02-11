fs_rtp_session_add_transmitter_gst_sink (FsRtpSession *self,
    FsTransmitter *transmitter,
    GError **error)
{
  GstElement *sink;

  g_object_get (transmitter, "gst-sink", &sink, NULL);

  if (!gst_bin_add (GST_BIN (self->priv->conference), sink))
  {
    g_set_error (error, FS_ERROR, FS_ERROR_CONSTRUCTION,
      "Could not add the transmitter sink for %s to the conference",
        G_OBJECT_TYPE_NAME(transmitter));
    goto error;
  }

  gst_element_sync_state_with_parent (sink);

  if (!_get_request_pad_and_link (self->priv->transmitter_rtp_tee,
      "rtp tee", sink, "sink1", GST_PAD_SINK, error))
    goto error;

  if (!_get_request_pad_and_link (self->priv->transmitter_rtcp_tee,
      "rtcp tee", sink, "sink2", GST_PAD_SINK, error))
    goto error;

  gst_object_unref (sink);

  return TRUE;

 error:
  if (sink)
    gst_object_unref (sink);

  return FALSE;
}

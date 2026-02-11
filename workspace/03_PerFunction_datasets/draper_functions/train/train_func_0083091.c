_state_changed (FsStreamTransmitter *stream_transmitter,
    guint component,
    FsStreamState state,
    gpointer user_data)
{
  FsRawStream *self = FS_RAW_STREAM (user_data);
  GstElement *conf = GST_ELEMENT (fs_raw_stream_get_conference (self, NULL));

  if (!conf)
    return;

  gst_element_post_message (conf,
      gst_message_new_element (GST_OBJECT (conf),
          gst_structure_new ("farstream-component-state-changed",
              "stream", FS_TYPE_STREAM, self,
              "component", G_TYPE_UINT, component,
              "state", FS_TYPE_STREAM_STATE, state,
              NULL)));

  gst_object_unref (conf);

  if (component == 1 && state == FS_STREAM_STATE_FAILED)
    fs_stream_emit_error (FS_STREAM (self), FS_ERROR_CONNECTION_FAILED,
        "Could not establish connection");
}

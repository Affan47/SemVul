gst_fd_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstFdSink *fdsink;

  fdsink = GST_FD_SINK (object);

  switch (prop_id) {
    case ARG_FD:{
      int fd;

      fd = g_value_get_int (value);
      gst_fd_sink_update_fd (fdsink, fd, NULL);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

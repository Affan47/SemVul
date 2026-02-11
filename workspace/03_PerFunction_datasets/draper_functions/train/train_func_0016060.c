gst_wrapper_camera_src_src_event_probe (GstPad * pad, GstEvent * evt,
    gpointer udata)
{
  gboolean ret = TRUE;
  GstWrapperCameraBinSrc *self = udata;

  switch (GST_EVENT_TYPE (evt)) {
    case GST_EVENT_EOS:

      ret = FALSE;
      break;
    case GST_EVENT_NEWSEGMENT:
      if (self->drop_newseg) {
        ret = FALSE;
        self->drop_newseg = FALSE;
      }
      break;
    default:
      break;
  }
  return ret;
}

gst_play_sink_convert_frame (GstPlaySink * playsink, GstCaps * caps)
{
  GstBuffer *result;

  result = gst_play_sink_get_last_frame (playsink);
  if (result != NULL && caps != NULL) {
    GstBuffer *temp;
    GError *err = NULL;

    temp = gst_video_convert_frame (result, caps, 25 * GST_SECOND, &err);
    gst_buffer_unref (result);
    if (temp == NULL && err) {


      GST_ERROR ("Error converting frame: %s", err->message);
      g_error_free (err);
    }
    result = temp;
  }
  return result;
}

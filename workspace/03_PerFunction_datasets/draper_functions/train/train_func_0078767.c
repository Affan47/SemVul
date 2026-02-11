gst_uvc_h264_src_buffer_probe (GstPad * pad, GstPadProbeInfo * info,
    gpointer user_data)
{
  GstUvcH264Src *self = GST_UVC_H264_SRC (user_data);
  GstBuffer *buffer = info->data;


  if (self->key_unit_event) {
    GstClockTime ts, running_time, stream_time;
    gboolean all_headers;
    guint count;
    GstEvent *downstream;

    if (gst_video_event_parse_upstream_force_key_unit (self->key_unit_event,
            &ts, &all_headers, &count)) {
      if (!GST_CLOCK_TIME_IS_VALID (ts)) {
        ts = GST_BUFFER_TIMESTAMP (buffer);
      }
      running_time = gst_segment_to_running_time (&self->segment,
          GST_FORMAT_TIME, ts);

      stream_time = gst_segment_to_stream_time (&self->segment,
          GST_FORMAT_TIME, ts);

      GST_DEBUG_OBJECT (self, "Sending downstream force-key-unit : %d - %d ts=%"
          GST_TIME_FORMAT " running time =%" GST_TIME_FORMAT " stream=%"
          GST_TIME_FORMAT, all_headers, count, GST_TIME_ARGS (ts),
          GST_TIME_ARGS (running_time), GST_TIME_ARGS (stream_time));
      downstream = gst_video_event_new_downstream_force_key_unit (ts,
          running_time, stream_time, all_headers, count);
      gst_pad_push_event (self->vidsrc, downstream);
      gst_event_replace (&self->key_unit_event, NULL);
    }
  }
  return TRUE;
}

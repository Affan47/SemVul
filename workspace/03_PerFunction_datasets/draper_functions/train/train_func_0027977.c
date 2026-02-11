have_subtitle (GstElement * appsink, App * app)
{
  GstBuffer *buffer;
  GstSample *sample;


  g_signal_emit_by_name (appsink, "pull-sample", &sample);
  if (sample) {
    GstMapInfo map;
    gint64 position;
    GstClock *clock;
    GstClockTime base_time, running_time;

    buffer = gst_sample_get_buffer (sample);
    gst_element_query_position (appsink, GST_FORMAT_TIME, &position);

    clock = gst_element_get_clock (appsink);
    base_time = gst_element_get_base_time (appsink);

    running_time = gst_clock_get_time (clock) - base_time;

    gst_object_unref (clock);

    g_message ("received a subtitle at position %" GST_TIME_FORMAT
        ", running_time %" GST_TIME_FORMAT, GST_TIME_ARGS (position),
        GST_TIME_ARGS (running_time));

    gst_buffer_map (buffer, &map, GST_MAP_READ);
    gst_util_dump_mem (map.data, map.size);
    gst_buffer_unmap (buffer, &map);
    gst_sample_unref (sample);
  }
  return GST_FLOW_OK;
}

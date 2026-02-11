gst_ogg_mux_push_buffer (GstOggMux * mux, GstBuffer * buffer,
    GstOggPadData * oggpad)
{
  GstCaps *caps;


  GST_BUFFER_OFFSET (buffer) = mux->offset;
  mux->offset += GST_BUFFER_SIZE (buffer);
  GST_BUFFER_OFFSET_END (buffer) = mux->offset;


  if (GST_BUFFER_TIMESTAMP_IS_VALID (buffer)) {
    gint64 run_time = GST_BUFFER_TIMESTAMP (buffer);
    if (mux->last_ts != GST_CLOCK_TIME_NONE && run_time < mux->last_ts)
      GST_BUFFER_TIMESTAMP (buffer) = mux->last_ts;
    else
      mux->last_ts = run_time;
  }

  caps = gst_pad_get_negotiated_caps (mux->srcpad);
  gst_buffer_set_caps (buffer, caps);
  if (caps)
    gst_caps_unref (caps);

  return gst_pad_push (mux->srcpad, buffer);
}

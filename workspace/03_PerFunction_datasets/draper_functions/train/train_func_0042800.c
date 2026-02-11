gst_output_selector_chain (GstPad * pad, GstBuffer * buf)
{
  GstFlowReturn res;
  GstOutputSelector *osel;
  GstClockTime last_stop, duration;

  osel = GST_OUTPUT_SELECTOR (gst_pad_get_parent (pad));


  while (osel->pending_srcpad) {

    gst_output_selector_switch (osel);
  }

  if (osel->latest_buffer) {
    gst_buffer_unref (osel->latest_buffer);
    osel->latest_buffer = NULL;
  }

  if (osel->resend_latest) {

    osel->latest_buffer = gst_buffer_ref (buf);
  }


  last_stop = GST_BUFFER_TIMESTAMP (buf);
  if (GST_CLOCK_TIME_IS_VALID (last_stop)) {
    duration = GST_BUFFER_DURATION (buf);
    if (GST_CLOCK_TIME_IS_VALID (duration)) {
      last_stop += duration;
    }
    GST_LOG_OBJECT (osel, "setting last stop %" GST_TIME_FORMAT,
        GST_TIME_ARGS (last_stop));
    gst_segment_set_last_stop (&osel->segment, osel->segment.format, last_stop);
  }

  GST_LOG_OBJECT (osel, "pushing buffer to %" GST_PTR_FORMAT,
      osel->active_srcpad);
  res = gst_pad_push (osel->active_srcpad, buf);
  gst_object_unref (osel);

  return res;
}

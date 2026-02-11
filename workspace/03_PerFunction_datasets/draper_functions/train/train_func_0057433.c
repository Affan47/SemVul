gst_output_selector_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstFlowReturn res;
  GstOutputSelector *osel;
  GstClockTime position, duration;

  osel = GST_OUTPUT_SELECTOR (parent);


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


  position = GST_BUFFER_TIMESTAMP (buf);
  if (GST_CLOCK_TIME_IS_VALID (position)) {
    duration = GST_BUFFER_DURATION (buf);
    if (GST_CLOCK_TIME_IS_VALID (duration)) {
      position += duration;
    }
    GST_LOG_OBJECT (osel, "setting last stop %" GST_TIME_FORMAT,
        GST_TIME_ARGS (position));
    osel->segment.position = position;
  }

  GST_LOG_OBJECT (osel, "pushing buffer to %" GST_PTR_FORMAT,
      osel->active_srcpad);
  res = gst_pad_push (osel->active_srcpad, buf);

  return res;
}

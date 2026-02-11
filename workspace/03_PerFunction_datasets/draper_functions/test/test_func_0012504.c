gst_base_sink_wait (GstBaseSink * sink, GstClockTime time,
    GstClockTimeDiff * jitter)
{
  GstClockReturn status;
  GstFlowReturn ret;

  do {
    GstClockTime stime;

    GST_DEBUG_OBJECT (sink, "checking preroll");


    while (G_UNLIKELY (sink->need_preroll)) {
      ret = gst_base_sink_wait_preroll (sink);
      if ((ret != GST_FLOW_OK) && (ret != GST_FLOW_STEP))
        goto flushing;
    }


    GST_DEBUG_OBJECT (sink, "possibly waiting for clock to reach %"
        GST_TIME_FORMAT, GST_TIME_ARGS (time));


    stime = gst_base_sink_adjust_time (sink, time);


    status = gst_base_sink_wait_clock (sink, stime, jitter);

    GST_DEBUG_OBJECT (sink, "clock returned %d", status);


    if (status == GST_CLOCK_BADTIME)
      break;


    if (G_UNLIKELY (sink->flushing))
      goto flushing;


  } while (status == GST_CLOCK_UNSCHEDULED);

  GST_DEBUG_OBJECT (sink, "end of stream");

  return GST_FLOW_OK;


flushing:
  {
    GST_DEBUG_OBJECT (sink, "we are flushing");
    return GST_FLOW_FLUSHING;
  }
}

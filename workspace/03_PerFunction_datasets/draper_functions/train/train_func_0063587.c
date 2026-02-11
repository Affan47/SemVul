gst_video_max_rate_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  GstVideoMaxRate *videomaxrate = GST_VIDEO_MAX_RATE (trans);
  GstClockTime ts = GST_BUFFER_TIMESTAMP (buf);

  if (!GST_BUFFER_TIMESTAMP_IS_VALID (buf) || videomaxrate->wanted_diff == 0)
    return GST_FLOW_OK;


  if (GST_CLOCK_TIME_IS_VALID (videomaxrate->last_ts)) {
    GstClockTimeDiff diff = ts - videomaxrate->last_ts;


    if (diff < videomaxrate->wanted_diff &&
        videomaxrate->average < videomaxrate->wanted_diff)
      return GST_BASE_TRANSFORM_FLOW_DROPPED;


    if (videomaxrate->average) {
      GstClockTimeDiff wanted_diff;

      if (G_LIKELY (videomaxrate->average_period > videomaxrate->wanted_diff))
        wanted_diff = videomaxrate->wanted_diff;
      else
        wanted_diff = videomaxrate->average_period * 10;

      videomaxrate->average =
          gst_util_uint64_scale_round (videomaxrate->average,
          videomaxrate->average_period - wanted_diff,
          videomaxrate->average_period) +
          gst_util_uint64_scale_round (diff, wanted_diff,
          videomaxrate->average_period);
    } else {
      videomaxrate->average = diff;
    }
  }

  videomaxrate->last_ts = ts;
  return GST_FLOW_OK;
}

gst_videomixer2_change_state (GstElement * element, GstStateChange transition)
{
  GstVideoMixer2 *mix = GST_VIDEO_MIXER2 (element);
  GstStateChangeReturn ret;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      mix->send_stream_start = TRUE;
      mix->send_caps = TRUE;
      gst_segment_init (&mix->segment, GST_FORMAT_TIME);
      gst_caps_replace (&mix->current_caps, NULL);
      GST_LOG_OBJECT (mix, "starting collectpads");
      gst_collect_pads_start (mix->collect);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      GST_LOG_OBJECT (mix, "stopping collectpads");
      gst_collect_pads_stop (mix->collect);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_videomixer2_reset (mix);
      break;
    default:
      break;
  }

  return ret;
}

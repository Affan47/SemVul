gst_buffer_straw_start_pipeline (GstElement * bin, GstPad * pad)
{
  GstStateChangeReturn ret;

  id = gst_pad_add_probe (pad, GST_PAD_PROBE_TYPE_BUFFER,
      buffer_probe, NULL, NULL);

  ret = gst_element_set_state (bin, GST_STATE_PLAYING);
  fail_if (ret == GST_STATE_CHANGE_FAILURE, "Could not start test pipeline");
  if (ret == GST_STATE_CHANGE_ASYNC) {
    ret = gst_element_get_state (bin, NULL, NULL, GST_CLOCK_TIME_NONE);
    fail_if (ret != GST_STATE_CHANGE_SUCCESS, "Could not start test pipeline");
  }
}

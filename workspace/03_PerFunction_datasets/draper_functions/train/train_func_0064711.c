gst_matroska_demux_sink_activate (GstPad * sinkpad)
{
  GstMatroskaDemux *demux = GST_MATROSKA_DEMUX (GST_PAD_PARENT (sinkpad));

  if (gst_pad_check_pull_range (sinkpad)) {
    GST_DEBUG ("going to pull mode");
    demux->streaming = FALSE;
    return gst_pad_activate_pull (sinkpad, TRUE);
  } else {
    GST_DEBUG ("going to push (streaming) mode");
    demux->streaming = TRUE;
    return gst_pad_activate_push (sinkpad, TRUE);
  }

  return FALSE;
}

gst_apexsink_reset (GstAudioSink * asink)
{
  int res;
  GstApExSink *apexsink = (GstApExSink *) asink;

  GST_INFO_OBJECT (apexsink, "RESET : flushing buffer...");

  if ((res = gst_apexraop_flush (apexsink->gst_apexraop)) == GST_RTSP_STS_OK) {
    GST_INFO_OBJECT (apexsink, "RESET : ApEx buffer flush success");
  } else {
    GST_WARNING_OBJECT (apexsink,
        "RESET : could not flush ApEx buffer, RTSP code=%d", res);
  }
}

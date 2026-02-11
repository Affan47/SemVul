rtsp_session_no_more_pads (GstElement * session, GstSDPDemux * demux)
{
  GST_DEBUG_OBJECT (demux, "got no-more-pads");
  gst_element_no_more_pads (GST_ELEMENT_CAST (demux));
}

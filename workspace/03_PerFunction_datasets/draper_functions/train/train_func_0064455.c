gst_rtp_ssrc_demux_reset (GstRtpSsrcDemux * demux)
{
  GSList *walk;

  for (walk = demux->srcpads; walk; walk = g_slist_next (walk)) {
    GstRtpSsrcDemuxPad *dpad = (GstRtpSsrcDemuxPad *) walk->data;

    gst_pad_set_active (dpad->rtp_pad, FALSE);
    gst_pad_set_active (dpad->rtcp_pad, FALSE);

    gst_element_remove_pad (GST_ELEMENT_CAST (demux), dpad->rtp_pad);
    gst_element_remove_pad (GST_ELEMENT_CAST (demux), dpad->rtcp_pad);
    g_free (dpad);
  }
  g_slist_free (demux->srcpads);
  demux->srcpads = NULL;
}
